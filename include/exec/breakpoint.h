/*
 * QEMU breakpoint & watchpoint definitions
 *
 * Copyright (c) 2012 SUSE LINUX Products GmbH
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef EXEC_BREAKPOINT_H
#define EXEC_BREAKPOINT_H

#include "qemu/queue.h"
#include "exec/vaddr.h"
#include "exec/memattrs.h"

#if defined(CONFIG_JOVE) || defined(CONFIG_JOVE_HELPERS)
#define JOVE_MS_STRUCT __attribute__((ms_struct))
#else
#define JOVE_MS_STRUCT
#endif

typedef struct JOVE_MS_STRUCT CPUBreakpoint {
    vaddr pc;
    int flags; /* BP_* */
    QTAILQ_ENTRY(CPUBreakpoint) entry;
} CPUBreakpoint;

typedef struct JOVE_MS_STRUCT CPUWatchpoint {
    vaddr vaddr_;
    vaddr len;
    vaddr hitaddr;
    MemTxAttrs hitattrs;
    int flags; /* BP_* */
    QTAILQ_ENTRY(CPUWatchpoint) entry;
} CPUWatchpoint;

#endif
