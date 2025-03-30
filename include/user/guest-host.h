/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * guest <-> host helpers.
 *
 *  Copyright (c) 2003 Fabrice Bellard
 */

#ifndef USER_GUEST_HOST_H
#define USER_GUEST_HOST_H

#include "exec/vaddr.h"
#include "user/guest-base.h"
#include "accel/tcg/cpu-ops.h"

/*
 * If non-zero, the guest virtual address space is a contiguous subset
 * of the host virtual address space, i.e. '-R reserved_va' is in effect
 * either from the command-line or by default.  The value is the last
 * byte of the guest address space e.g. UINT32_MAX.
 *
 * If zero, the host and guest virtual address spaces are intermingled.
 */
extern unsigned long reserved_va;

/*
 * The last byte of the guest address space.
 * If reserved_va is non-zero, guest_addr_max matches.
 * If reserved_va is zero, guest_addr_max equals the full guest space.
 */
extern unsigned long guest_addr_max;

static inline vaddr cpu_untagged_addr(CPUState *cs, vaddr x)
{
    const TCGCPUOps *tcg_ops = cs->cc->tcg_ops;
    if (tcg_ops->untagged_addr) {
        return tcg_ops->untagged_addr(cs, x);
    }
    return x;
}

#ifdef CONFIG_JOVE_HELPERS

/* All direct uses of g2h and h2g need to go away for usermode softmmu.  */
static inline void *g2h_untagged(vaddr x)
{
    return (void *)(x);
}

#else

#ifdef CONFIG_JOVE
void *_jv_g2h(uint64_t Addr);
#endif

static inline void *g2h_untagged(vaddr x)
{
#ifdef CONFIG_JOVE
    void *y = _jv_g2h(x);
    if (y)
      return y;
    return (void *)x;
#else
    return (void *)((uintptr_t)(x) + guest_base);
#endif
}

#endif

static inline void *g2h(CPUState *cs, vaddr x)
{
    return g2h_untagged(cpu_untagged_addr(cs, x));
}

static inline bool guest_addr_valid_untagged(vaddr x)
{
    return x <= guest_addr_max;
}

static inline bool guest_range_valid_untagged(vaddr start, vaddr len)
{
    return len - 1 <= guest_addr_max && start <= guest_addr_max - len + 1;
}
 
#ifdef CONFIG_JOVE_HELPERS

#define h2g_valid(x) true

#define h2g_nocheck(x) ({ \
    uintptr_t __ret = (uintptr_t)(x); \
    (abi_ptr)__ret; \
})

#define h2g(x) ({ h2g_nocheck(x); })

#else

#define h2g_valid(x) \
    ((uintptr_t)(x) - guest_base <= guest_addr_max)

#define h2g_nocheck(x) ({ \
    uintptr_t __ret = (uintptr_t)(x) - guest_base; \
    (vaddr)__ret; \
})

#define h2g(x) ({ \
    /* Check if given address fits target address space */ \
    assert(h2g_valid(x)); \
    h2g_nocheck(x); \
})

#endif /* CONFIG_JOVE_HELPERS */

#endif
