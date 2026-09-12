#ifndef JOVE_HELPER_BY_NAME
#error
#endif

#define DEF_HELPER_FLAGS_0(name, flags, ret)                             JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_1(name, flags, ret, t1)                         JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_2(name, flags, ret, t1, t2)                     JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_3(name, flags, ret, t1, t2, t3)                 JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_4(name, flags, ret, t1, t2, t3, t4)             JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_5(name, flags, ret, t1, t2, t3, t4, t5)         JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_6(name, flags, ret, t1, t2, t3, t4, t5, t6)     JOVE_HELPER_BY_NAME(name);
#define DEF_HELPER_FLAGS_7(name, flags, ret, t1, t2, t3, t4, t5, t6, t7) JOVE_HELPER_BY_NAME(name);

#define IN_HELPER_PROTO

#include HELPER_H

#undef IN_HELPER_PROTO

#undef DEF_HELPER_FLAGS_0
#undef DEF_HELPER_FLAGS_1
#undef DEF_HELPER_FLAGS_2
#undef DEF_HELPER_FLAGS_3
#undef DEF_HELPER_FLAGS_4
#undef DEF_HELPER_FLAGS_5
#undef DEF_HELPER_FLAGS_6
#undef DEF_HELPER_FLAGS_7
