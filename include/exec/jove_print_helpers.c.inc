void _jove_print_helpers(void) {
#define JOVE_HELPER_BY_NAME(name)                                              \
  do {                                                                         \
    printf("%s\n", #name);                                                     \
  } while (0)

#define HELPER_H "helper.h"
#include "exec/jove_helpers_by_name.c.inc"
}
