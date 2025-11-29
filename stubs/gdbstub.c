#include "qemu/osdep.h"
#include "exec/gdbstub.h"       /* gdb_static_features */

#ifndef CONFIG_JOVE

const GDBFeature gdb_static_features[] = {
  { NULL }
};

#endif
