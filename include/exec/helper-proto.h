/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Helper file for declaring TCG helper functions.
 * This one expands prototypes for the helper functions.
 */

#if !defined(HELPER_PROTO_H) || defined(HELPER_PROTO_H_INC_FOR_JOVE)
#define HELPER_PROTO_H

#include "exec/helper-proto-common.h"

#define HELPER_H "helper.h"
#include "exec/helper-proto.h.inc"
#undef  HELPER_H

#endif /* HELPER_PROTO_H */
