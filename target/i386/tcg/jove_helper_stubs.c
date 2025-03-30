/* the purpose of these definitions is to enable the linking step to succeed */
double _jove_sin(double) {
  __builtin_trap();
  __builtin_unreachable();
}
double _jove_cos(double) {
  __builtin_trap();
  __builtin_unreachable();
}
double _jove_tan(double) {
  __builtin_trap();
  __builtin_unreachable();
}
