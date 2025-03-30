#pragma once

#define JV_FUNC_ATTR __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

#define JOVE_PCREL_MAGIC 0xb7432f22

JV_FUNC_ATTR int jv_init_libqemu(const char *);

JV_FUNC_ATTR void *jv_get_tcg_context(void);

JV_FUNC_ATTR int jv_tcgopc_nb_iargs_in_def(unsigned opc);
JV_FUNC_ATTR int jv_tcgopc_nb_oargs_in_def(unsigned opc);
JV_FUNC_ATTR int jv_tcgopc_nb_cargs_in_def(unsigned opc);
JV_FUNC_ATTR const char *jv_tcgopc_name_in_def(unsigned opc);

JV_FUNC_ATTR const char *jv_tcg_find_helper(void *);

JV_FUNC_ATTR const char *jv_tcg_get_arg_str(char *buf, int buf_size,
                                            uint64_t arg);

JV_FUNC_ATTR const char *jv_get_global_name(int);

JV_FUNC_ATTR void jv_tcg_func_start(void *ctx);

JV_FUNC_ATTR uint32_t jv_hflags_of_cpu_env(CPUState *cpu);

JV_FUNC_ATTR void jv_init_tcg_ctx(void *ctx);

JV_FUNC_ATTR void jv_term_is_cond_jump(uint64_t Target, uint64_t NextPC);
JV_FUNC_ATTR void jv_term_is_uncond_jump(uint64_t Target);
JV_FUNC_ATTR void jv_term_is_ind_call(uint64_t NextPC);
JV_FUNC_ATTR void jv_term_is_ind_jump(void);
JV_FUNC_ATTR void jv_term_is_return(void);
JV_FUNC_ATTR void jv_term_is_call(uint64_t Target, uint64_t NextPC);
JV_FUNC_ATTR void jv_term_is_none(uint64_t NextPC);
JV_FUNC_ATTR void jv_term_is_unreachable(void);
JV_FUNC_ATTR bool jv_is_term_unknown(void);
JV_FUNC_ATTR uint64_t jv_get_end_pc(void);
JV_FUNC_ATTR void jv_term_addr_is(uint64_t Addr);

JV_FUNC_ATTR bool jv_is_term_ind_call(void);
JV_FUNC_ATTR bool jv_is_term_call(void);

JV_FUNC_ATTR void jv_ind_call_term_next_pc_is(uint64_t NextPC);
JV_FUNC_ATTR void jv_call_term_next_pc_is(uint64_t NextPC);

JV_FUNC_ATTR void jv_set_end_pc(uint64_t);

JV_FUNC_ATTR void jv_illegal_op(uint64_t PC);

#ifdef __cplusplus
}
#endif
