#define JOVE_CONCAT3_(a, b, c) a##b##c
#define JOVE_CONCAT3(a, b, c) JOVE_CONCAT3_(a, b, c)

#ifndef JOVE_ARE_CORE_HELPERS
#define JOVE_ARE_CORE_HELPERS 0
#endif

#if JOVE_ARE_CORE_HELPERS == 1
#define JOVE_CORE_HELPERS _core_
#else
#define JOVE_CORE_HELPERS _
#endif

const void *const JOVE_CONCAT3(__jove_all,JOVE_CORE_HELPERS,helpers)[] = {
#define JOVE_HELPER_BY_NAME(name)                                              \
  (const void *)(helper ## _ ## name), \
  (const void *)(#name),

#ifndef HELPER_H
#define HELPER_H "helper.h"
#endif
#include "exec/jove_helpers_by_name.c.inc"

  NULL
};
