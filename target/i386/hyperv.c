/*
 * QEMU KVM Hyper-V support
 *
 * Copyright (C) 2015 Andrey Smetanin <asmetanin@virtuozzo.com>
 *
 * Authors:
 *  Andrey Smetanin <asmetanin@virtuozzo.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "qemu/main-loop.h"
#include "hyperv.h"
#include "hyperv-proto.h"

struct HvSintRoute {
    uint32_t sint;
    X86CPU *cpu;
    int gsi;
    EventNotifier sint_set_notifier;
    EventNotifier sint_ack_notifier;
    HvSintAckClb sint_ack_clb;
    void *sint_ack_clb_data;
    unsigned refcount;
};

uint32_t hyperv_vp_index(X86CPU *cpu)
{
    return CPU(cpu)->cpu_index;
}

X86CPU *hyperv_find_vcpu(uint32_t vp_index)
{
    return X86_CPU(qemu_get_cpu(vp_index));
}

int kvm_hv_handle_exit(X86CPU *cpu, struct kvm_hyperv_exit *exit)
{
    CPUX86State *env = &cpu->env;

    switch (exit->type) {
    case KVM_EXIT_HYPERV_SYNIC:
        if (!cpu->hyperv_synic) {
            return -1;
        }

        /*
         * For now just track changes in SynIC control and msg/evt pages msr's.
         * When SynIC messaging/events processing will be added in future
         * here we will do messages queues flushing and pages remapping.
         */
        switch (exit->u.synic.msr) {
        case HV_X64_MSR_SCONTROL:
            env->msr_hv_synic_control = exit->u.synic.control;
            break;
        case HV_X64_MSR_SIMP:
            env->msr_hv_synic_msg_page = exit->u.synic.msg_page;
            break;
        case HV_X64_MSR_SIEFP:
            env->msr_hv_synic_evt_page = exit->u.synic.evt_page;
            break;
        default:
            return -1;
        }
        return 0;
    case KVM_EXIT_HYPERV_HCALL: {
        uint16_t code;

        code  = exit->u.hcall.input & 0xffff;
        switch (code) {
        case HV_POST_MESSAGE:
        case HV_SIGNAL_EVENT:
        default:
            exit->u.hcall.result = HV_STATUS_INVALID_HYPERCALL_CODE;
            return 0;
        }
    }
    default:
        return -1;
    }
}

static void kvm_hv_sint_ack_handler(EventNotifier *notifier)
{
    HvSintRoute *sint_route = container_of(notifier, HvSintRoute,
                                           sint_ack_notifier);
    event_notifier_test_and_clear(notifier);
    sint_route->sint_ack_clb(sint_route->sint_ack_clb_data);
}

HvSintRoute *hyperv_sint_route_new(uint32_t vp_index, uint32_t sint,
                                   HvSintAckClb sint_ack_clb,
                                   void *sint_ack_clb_data)
{
    HvSintRoute *sint_route;
    EventNotifier *ack_notifier;
    int r, gsi;
    X86CPU *cpu;

    cpu = hyperv_find_vcpu(vp_index);
    if (!cpu) {
        return NULL;
    }

    sint_route = g_new0(HvSintRoute, 1);
    r = event_notifier_init(&sint_route->sint_set_notifier, false);
    if (r) {
        goto err;
    }

    ack_notifier = sint_ack_clb ? &sint_route->sint_ack_notifier : NULL;
    if (ack_notifier) {
        r = event_notifier_init(ack_notifier, false);
        if (r) {
            goto err_sint_set_notifier;
        }

        event_notifier_set_handler(ack_notifier, kvm_hv_sint_ack_handler);
    }

    gsi = kvm_irqchip_add_hv_sint_route(kvm_state, vp_index, sint);
    if (gsi < 0) {
        goto err_gsi;
    }

    r = kvm_irqchip_add_irqfd_notifier_gsi(kvm_state,
                                           &sint_route->sint_set_notifier,
                                           ack_notifier, gsi);
    if (r) {
        goto err_irqfd;
    }
    sint_route->gsi = gsi;
    sint_route->sint_ack_clb = sint_ack_clb;
    sint_route->sint_ack_clb_data = sint_ack_clb_data;
    sint_route->cpu = cpu;
    sint_route->sint = sint;
    sint_route->refcount = 1;

    return sint_route;

err_irqfd:
    kvm_irqchip_release_virq(kvm_state, gsi);
err_gsi:
    if (ack_notifier) {
        event_notifier_set_handler(ack_notifier, NULL);
        event_notifier_cleanup(ack_notifier);
    }
err_sint_set_notifier:
    event_notifier_cleanup(&sint_route->sint_set_notifier);
err:
    g_free(sint_route);

    return NULL;
}

void hyperv_sint_route_ref(HvSintRoute *sint_route)
{
    sint_route->refcount++;
}

void hyperv_sint_route_unref(HvSintRoute *sint_route)
{
    if (!sint_route) {
        return;
    }

    assert(sint_route->refcount > 0);

    if (--sint_route->refcount) {
        return;
    }

    kvm_irqchip_remove_irqfd_notifier_gsi(kvm_state,
                                          &sint_route->sint_set_notifier,
                                          sint_route->gsi);
    kvm_irqchip_release_virq(kvm_state, sint_route->gsi);
    if (sint_route->sint_ack_clb) {
        event_notifier_set_handler(&sint_route->sint_ack_notifier, NULL);
        event_notifier_cleanup(&sint_route->sint_ack_notifier);
    }
    event_notifier_cleanup(&sint_route->sint_set_notifier);
    g_free(sint_route);
}

int hyperv_sint_route_set_sint(HvSintRoute *sint_route)
{
    return event_notifier_set(&sint_route->sint_set_notifier);
}
