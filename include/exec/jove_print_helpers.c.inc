extern const void *const __jove_all_core_helpers[];

unsigned _jove_helper_count(void) {
  unsigned c = 0;

  for (const void *const *p = __jove_all_core_helpers; *p; p += 2)
    ++c;
  for (const void *const *p = __jove_all_helpers; *p; p += 2)
    ++c;

  return c;
}

void _jove_print_helpers(void) {
  for (const void *const *p = __jove_all_core_helpers; *p; p += 2) {
    const char *const name = (const char *)p[1];

    printf("%s\n", name);
  }
  for (const void *const *p = __jove_all_helpers; *p; p += 2) {
    const char *const name = (const char *)p[1];

    printf("%s\n", name);
  }
}
