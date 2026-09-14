#include "exec/jove_print_helpers.c.inc"

void *const *jv_special_helpers(void) {
  static void *const special_helpers[] = {
    &helper_lookup_tb_ptr,
    &helper_memset,
#if defined(TARGET_X86_64)
    &helper_syscall
#elif defined(TARGET_I386)
    &helper_raise_interrupt
#elif defined(TARGET_AARCH64)
    &helper_info_exception_with_syndrome.func
#elif defined(TARGET_MIPS64) || defined(TARGET_MIPS)
    &helper_raise_exception_err
#else
#error
#endif
  };

  return special_helpers;
}
