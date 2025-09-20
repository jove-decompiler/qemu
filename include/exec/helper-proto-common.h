/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Helper file for declaring TCG helper functions.
 * This one expands prototypes for the helper functions.
 */

#if !defined(HELPER_PROTO_COMMON_H) || defined(HELPER_PROTO_H_INC_FOR_JOVE)
#define HELPER_PROTO_COMMON_H

#include "qemu/atomic128.h"  /* for HAVE_CMPXCHG128 */

#define HELPER_H "accel/tcg/tcg-runtime.h"
#include "exec/helper-proto.h.inc"
#undef  HELPER_H

#include "accel/tcg/getpc.h"

#endif /* HELPER_PROTO_COMMON_H */
