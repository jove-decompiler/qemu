#define CONFIG_MIPS_L1_CACHE_SHIFT 6

#define __LITTLE_ENDIAN 1234

# define __force

#define ___PASTE(a,b) a##b

#define __PASTE(a,b) ___PASTE(a,b)

#define __always_inline                 inline __attribute__((__always_inline__))

#define __attribute_const__             __attribute__((__const__))

#define __gnu_inline                    __attribute__((__gnu_inline__))

#define __pure                          __attribute__((__pure__))

#define __section(section)              __attribute__((__section__(section)))

#define __maybe_unused                  __attribute__((__unused__))

#define __used                          __attribute__((__used__))

#define __weak                          __attribute__((__weak__))

#define MIPS_ISA_LEVEL "mips64r2"

#define notrace			__attribute__((__no_instrument_function__))

#define inline inline __gnu_inline __inline_maybe_unused notrace

#define __inline_maybe_unused __maybe_unused

typedef unsigned char __u8;

typedef unsigned int __u32;

typedef unsigned long long __u64;

typedef __u8  u8;

typedef __u32 u32;

typedef __u64 u64;

#if 0
typedef unsigned int	__kernel_size_t;
#endif

#define __bitwise

typedef __u32 __bitwise __le32;

#if 0
typedef _Bool			bool;

typedef __kernel_size_t		size_t;

typedef u32			uint32_t;

typedef u64			uint64_t;
#endif

#define CRC32_POLY_LE 0xedb88320

# define likely(x)	__builtin_expect(!!(x), 1)

# define unlikely(x)	__builtin_expect(!!(x), 0)

#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#define ___ADDRESSABLE(sym, __attrs) \
	static void * __used __attrs \
		__UNIQUE_ID(__PASTE(__addressable_,sym)) = (void *)&sym;

#define __ADDRESSABLE(sym) \
	___ADDRESSABLE(sym, __section(".discard.addressable"))

#define __stringify_1(x...)	#x

#define __stringify(x...)	__stringify_1(x)

#define __EXPORT_SYMBOL_REF(sym)			\
	.balign 4				ASM_NL	\
	.long sym

#define ___EXPORT_SYMBOL(sym, license, ns)		\
	.section ".export_symbol","a"		ASM_NL	\
	__export_symbol_##sym:			ASM_NL	\
		.asciz license			ASM_NL	\
		.asciz ns			ASM_NL	\
		__EXPORT_SYMBOL_REF(sym)	ASM_NL	\
	.previous

#define __EXPORT_SYMBOL(sym, license, ns)			\
	extern typeof(sym) sym;					\
	__ADDRESSABLE(sym)					\
	asm(__stringify(___EXPORT_SYMBOL(sym, license, ns)))

#define _EXPORT_SYMBOL(sym, license)	__EXPORT_SYMBOL(sym, license, "")

#define EXPORT_SYMBOL(sym)		_EXPORT_SYMBOL(sym, "")

#define ASM_NL		 ;

#define L1_CACHE_SHIFT		CONFIG_MIPS_L1_CACHE_SHIFT

#define L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#define SMP_CACHE_BYTES L1_CACHE_BYTES

#define ____cacheline_aligned __attribute__((__aligned__(SMP_CACHE_BYTES)))

#define do_div64_32(res, high, low, base) ({				\
	unsigned long __cf, __tmp, __tmp2, __i;				\
	unsigned long __quot32, __mod32;				\
									\
	__asm__(							\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	.set	noreorder				\n"	\
	"	move	%2, $0					\n"	\
	"	move	%3, $0					\n"	\
	"	b	1f					\n"	\
	"	 li	%4, 0x21				\n"	\
	"0:							\n"	\
	"	sll	$1, %0, 0x1				\n"	\
	"	srl	%3, %0, 0x1f				\n"	\
	"	or	%0, $1, %5				\n"	\
	"	sll	%1, %1, 0x1				\n"	\
	"	sll	%2, %2, 0x1				\n"	\
	"1:							\n"	\
	"	bnez	%3, 2f					\n"	\
	"	 sltu	%5, %0, %z6				\n"	\
	"	bnez	%5, 3f					\n"	\
	"2:							\n"	\
	"	 addiu	%4, %4, -1				\n"	\
	"	subu	%0, %0, %z6				\n"	\
	"	addiu	%2, %2, 1				\n"	\
	"3:							\n"	\
	"	bnez	%4, 0b					\n"	\
	"	 srl	%5, %1, 0x1f				\n"	\
	"	.set	pop"						\
	: "=&r" (__mod32), "=&r" (__tmp),				\
	  "=&r" (__quot32), "=&r" (__cf),				\
	  "=&r" (__i), "=&r" (__tmp2)					\
	: "Jr" (base), "0" (high), "1" (low));				\
									\
	(res) = __quot32;						\
	__mod32;							\
})

#define __div64_32(n, base) ({						\
	unsigned long __upper, __low, __high, __radix;			\
	unsigned long long __quot;					\
	unsigned long long __div;					\
	unsigned long __mod;						\
									\
	__div = (*n);							\
	__radix = (base);						\
									\
	__high = __div >> 32;						\
	__low = __div;							\
									\
	if (__high < __radix) {						\
		__upper = __high;					\
		__high = 0;						\
	} else {							\
		__upper = __high % __radix;				\
		__high /= __radix;					\
	}								\
									\
	__mod = do_div64_32(__low, __upper, __low, __radix);		\
									\
	__quot = __high;						\
	__quot = __quot << 32 | __low;					\
	(*n) = __quot;							\
	__mod;								\
})

#define ___constant_swahw32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x0000ffffUL) << 16) |		\
	(((__u32)(x) & (__u32)0xffff0000UL) >> 16)))

static inline __attribute_const__ __u32 __fswahw32(__u32 val)
{
#ifdef __arch_swahw32
	return __arch_swahw32(val);
#else
	return ___constant_swahw32(val);
#endif
}

#define __swahw32(x)				\
	(__builtin_constant_p((__u32)(x)) ?	\
	___constant_swahw32(x) :		\
	__fswahw32(x))

static inline __u32 __swahw32p(const __u32 *p)
{
#ifdef __arch_swahw32p
	return __arch_swahw32p(p);
#else
	return __swahw32(*p);
#endif
}

#define __cpu_to_le32(x) ((__force __le32)(__u32)(x))

#define __le32_to_cpu(x) ((__force __u32)(__le32)(x))

#define cpu_to_le32 __cpu_to_le32

#define cpu_has_clo_clz		1

static inline int fls(unsigned int x)
{
	int r;

	if (!__builtin_constant_p(x) &&
	    __builtin_constant_p(cpu_has_clo_clz) && cpu_has_clo_clz) {
		__asm__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_LEVEL"			\n"
		"	clz	%0, %1					\n"
		"	.set	pop					\n"
		: "=r" (x)
		: "r" (x));

		return 32 - x;
	}

	r = 32;
	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}

static __always_inline int fls64(__u64 x)
{
	__u32 h = x >> 32;
	if (h)
		return fls(h) + 32;
	return fls(x);
}

static __always_inline __attribute__((const))
int __ilog2_u32(u32 n)
{
	return fls(n) - 1;
}

static __always_inline __attribute__((const))
int __ilog2_u64(u64 n)
{
	return fls64(n) - 1;
}

#if 0
static inline __attribute__((const))
bool is_power_of_2(unsigned long n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}
#endif

#define ilog2(n) \
( \
	__builtin_constant_p(n) ?	\
	((n) < 2 ? 0 :			\
	 63 - __builtin_clzll(n)) :	\
	(sizeof(n) <= 4) ?		\
	__ilog2_u32(n) :		\
	__ilog2_u64(n)			\
 )

static inline __attribute_const__
int __order_base_2(unsigned long n)
{
	return n > 1 ? ilog2(n - 1) + 1 : 0;
}

#define __div64_const32(n, ___b)					\
({									\
	/*								\
	 * Multiplication by reciprocal of b: n / b = n * (p / b) / p	\
	 *								\
	 * We rely on the fact that most of this code gets optimized	\
	 * away at compile time due to constant propagation and only	\
	 * a few multiplication instructions should remain.		\
	 * Hence this monstrous macro (static inline doesn't always	\
	 * do the trick here).						\
	 */								\
	uint64_t ___res, ___x, ___t, ___m, ___n = (n);			\
	uint32_t ___p, ___bias;						\
									\
	/* determine MSB of b */					\
	___p = 1 << ilog2(___b);					\
									\
	/* compute m = ((p << 64) + b - 1) / b */			\
	___m = (~0ULL / ___b) * ___p;					\
	___m += (((~0ULL % ___b + 1) * ___p) + ___b - 1) / ___b;	\
									\
	/* one less than the dividend with highest result */		\
	___x = ~0ULL / ___b * ___b - 1;					\
									\
	/* test our ___m with res = m * x / (p << 64) */		\
	___res = ((___m & 0xffffffff) * (___x & 0xffffffff)) >> 32;	\
	___t = ___res += (___m & 0xffffffff) * (___x >> 32);		\
	___res += (___x & 0xffffffff) * (___m >> 32);			\
	___t = (___res < ___t) ? (1ULL << 32) : 0;			\
	___res = (___res >> 32) + ___t;					\
	___res += (___m >> 32) * (___x >> 32);				\
	___res /= ___p;							\
									\
	/* Now sanitize and optimize what we've got. */			\
	if (~0ULL % (___b / (___b & -___b)) == 0) {			\
		/* special case, can be simplified to ... */		\
		___n /= (___b & -___b);					\
		___m = ~0ULL / (___b / (___b & -___b));			\
		___p = 1;						\
		___bias = 1;						\
	} else if (___res != ___x / ___b) {				\
		/*							\
		 * We can't get away without a bias to compensate	\
		 * for bit truncation errors.  To avoid it we'd need an	\
		 * additional bit to represent m which would overflow	\
		 * a 64-bit variable.					\
		 *							\
		 * Instead we do m = p / b and n / b = (n * m + m) / p.	\
		 */							\
		___bias = 1;						\
		/* Compute m = (p << 64) / b */				\
		___m = (~0ULL / ___b) * ___p;				\
		___m += ((~0ULL % ___b + 1) * ___p) / ___b;		\
	} else {							\
		/*							\
		 * Reduce m / p, and try to clear bit 31 of m when	\
		 * possible, otherwise that'll need extra overflow	\
		 * handling later.					\
		 */							\
		uint32_t ___bits = -(___m & -___m);			\
		___bits |= ___m >> 32;					\
		___bits = (~___bits) << 1;				\
		/*							\
		 * If ___bits == 0 then setting bit 31 is  unavoidable.	\
		 * Simply apply the maximum possible reduction in that	\
		 * case. Otherwise the MSB of ___bits indicates the	\
		 * best reduction we should apply.			\
		 */							\
		if (!___bits) {						\
			___p /= (___m & -___m);				\
			___m /= (___m & -___m);				\
		} else {						\
			___p >>= ilog2(___bits);			\
			___m >>= ilog2(___bits);			\
		}							\
		/* No bias needed. */					\
		___bias = 0;						\
	}								\
									\
	/*								\
	 * Now we have a combination of 2 conditions:			\
	 *								\
	 * 1) whether or not we need to apply a bias, and		\
	 *								\
	 * 2) whether or not there might be an overflow in the cross	\
	 *    product determined by (___m & ((1 << 63) | (1 << 31))).	\
	 *								\
	 * Select the best way to do (m_bias + m * n) / (1 << 64).	\
	 * From now on there will be actual runtime code generated.	\
	 */								\
	___res = __arch_xprod_64(___m, ___n, ___bias);			\
									\
	___res /= ___p;							\
})

# define do_div(n,base) ({				\
	uint32_t __base = (base);			\
	uint32_t __rem;					\
	(void)(((typeof((n)) *)0) == ((uint64_t *)0));	\
	if (__builtin_constant_p(__base) &&		\
	    is_power_of_2(__base)) {			\
		__rem = (n) & (__base - 1);		\
		(n) >>= ilog2(__base);			\
	} else if (__builtin_constant_p(__base) &&	\
		   __base != 0) {			\
		uint32_t __res_lo, __n_lo = (n);	\
		(n) = __div64_const32(n, __base);	\
		/* the remainder can be computed with 32-bit regs */ \
		__res_lo = (n);				\
		__rem = __n_lo - __res_lo * __base;	\
	} else if (likely(((n) >> 32) == 0)) {		\
		__rem = (uint32_t)(n) % __base;		\
		(n) = (uint32_t)(n) / __base;		\
	} else {					\
		__rem = __div64_32(&(n), __base);	\
	}						\
	__rem;						\
 })

static inline uint64_t __arch_xprod_64(const uint64_t m, uint64_t n, bool bias)
{
	uint32_t m_lo = m;
	uint32_t m_hi = m >> 32;
	uint32_t n_lo = n;
	uint32_t n_hi = n >> 32;
	uint64_t res;
	uint32_t res_lo, res_hi, tmp;

	if (!bias) {
		res = ((uint64_t)m_lo * n_lo) >> 32;
	} else if (!(m & ((1ULL << 63) | (1ULL << 31)))) {
		/* there can't be any overflow here */
		res = (m + (uint64_t)m_lo * n_lo) >> 32;
	} else {
		res = m + (uint64_t)m_lo * n_lo;
		res_lo = res >> 32;
		res_hi = (res_lo < m_hi);
		res = res_lo | ((uint64_t)res_hi << 32);
	}

	if (!(m & ((1ULL << 63) | (1ULL << 31)))) {
		/* there can't be any overflow here */
		res += (uint64_t)m_lo * n_hi;
		res += (uint64_t)m_hi * n_lo;
		res >>= 32;
	} else {
		res += (uint64_t)m_lo * n_hi;
		tmp = res >> 32;
		res += (uint64_t)m_hi * n_lo;
		res_lo = res >> 32;
		res_hi = (res_lo < tmp);
		res = res_lo | ((uint64_t)res_hi << 32);
	}

	res += (uint64_t)m_hi * n_hi;

	return res;
}

static inline u64 div_u64_rem(u64 dividend, u32 divisor, u32 *remainder)
{
	*remainder = do_div(dividend, divisor);
	return dividend;
}

# define CRC_LE_BITS 64

# define tole(x) ((__force u32) cpu_to_le32(x))

static const u32 ____cacheline_aligned crc32table_le[8][256] = {{
tole(0x00000000L), tole(0x77073096L), tole(0xee0e612cL), tole(0x990951baL), 
tole(0x076dc419L), tole(0x706af48fL), tole(0xe963a535L), tole(0x9e6495a3L), 
tole(0x0edb8832L), tole(0x79dcb8a4L), tole(0xe0d5e91eL), tole(0x97d2d988L), 
tole(0x09b64c2bL), tole(0x7eb17cbdL), tole(0xe7b82d07L), tole(0x90bf1d91L), 
tole(0x1db71064L), tole(0x6ab020f2L), tole(0xf3b97148L), tole(0x84be41deL), 
tole(0x1adad47dL), tole(0x6ddde4ebL), tole(0xf4d4b551L), tole(0x83d385c7L), 
tole(0x136c9856L), tole(0x646ba8c0L), tole(0xfd62f97aL), tole(0x8a65c9ecL), 
tole(0x14015c4fL), tole(0x63066cd9L), tole(0xfa0f3d63L), tole(0x8d080df5L), 
tole(0x3b6e20c8L), tole(0x4c69105eL), tole(0xd56041e4L), tole(0xa2677172L), 
tole(0x3c03e4d1L), tole(0x4b04d447L), tole(0xd20d85fdL), tole(0xa50ab56bL), 
tole(0x35b5a8faL), tole(0x42b2986cL), tole(0xdbbbc9d6L), tole(0xacbcf940L), 
tole(0x32d86ce3L), tole(0x45df5c75L), tole(0xdcd60dcfL), tole(0xabd13d59L), 
tole(0x26d930acL), tole(0x51de003aL), tole(0xc8d75180L), tole(0xbfd06116L), 
tole(0x21b4f4b5L), tole(0x56b3c423L), tole(0xcfba9599L), tole(0xb8bda50fL), 
tole(0x2802b89eL), tole(0x5f058808L), tole(0xc60cd9b2L), tole(0xb10be924L), 
tole(0x2f6f7c87L), tole(0x58684c11L), tole(0xc1611dabL), tole(0xb6662d3dL), 
tole(0x76dc4190L), tole(0x01db7106L), tole(0x98d220bcL), tole(0xefd5102aL), 
tole(0x71b18589L), tole(0x06b6b51fL), tole(0x9fbfe4a5L), tole(0xe8b8d433L), 
tole(0x7807c9a2L), tole(0x0f00f934L), tole(0x9609a88eL), tole(0xe10e9818L), 
tole(0x7f6a0dbbL), tole(0x086d3d2dL), tole(0x91646c97L), tole(0xe6635c01L), 
tole(0x6b6b51f4L), tole(0x1c6c6162L), tole(0x856530d8L), tole(0xf262004eL), 
tole(0x6c0695edL), tole(0x1b01a57bL), tole(0x8208f4c1L), tole(0xf50fc457L), 
tole(0x65b0d9c6L), tole(0x12b7e950L), tole(0x8bbeb8eaL), tole(0xfcb9887cL), 
tole(0x62dd1ddfL), tole(0x15da2d49L), tole(0x8cd37cf3L), tole(0xfbd44c65L), 
tole(0x4db26158L), tole(0x3ab551ceL), tole(0xa3bc0074L), tole(0xd4bb30e2L), 
tole(0x4adfa541L), tole(0x3dd895d7L), tole(0xa4d1c46dL), tole(0xd3d6f4fbL), 
tole(0x4369e96aL), tole(0x346ed9fcL), tole(0xad678846L), tole(0xda60b8d0L), 
tole(0x44042d73L), tole(0x33031de5L), tole(0xaa0a4c5fL), tole(0xdd0d7cc9L), 
tole(0x5005713cL), tole(0x270241aaL), tole(0xbe0b1010L), tole(0xc90c2086L), 
tole(0x5768b525L), tole(0x206f85b3L), tole(0xb966d409L), tole(0xce61e49fL), 
tole(0x5edef90eL), tole(0x29d9c998L), tole(0xb0d09822L), tole(0xc7d7a8b4L), 
tole(0x59b33d17L), tole(0x2eb40d81L), tole(0xb7bd5c3bL), tole(0xc0ba6cadL), 
tole(0xedb88320L), tole(0x9abfb3b6L), tole(0x03b6e20cL), tole(0x74b1d29aL), 
tole(0xead54739L), tole(0x9dd277afL), tole(0x04db2615L), tole(0x73dc1683L), 
tole(0xe3630b12L), tole(0x94643b84L), tole(0x0d6d6a3eL), tole(0x7a6a5aa8L), 
tole(0xe40ecf0bL), tole(0x9309ff9dL), tole(0x0a00ae27L), tole(0x7d079eb1L), 
tole(0xf00f9344L), tole(0x8708a3d2L), tole(0x1e01f268L), tole(0x6906c2feL), 
tole(0xf762575dL), tole(0x806567cbL), tole(0x196c3671L), tole(0x6e6b06e7L), 
tole(0xfed41b76L), tole(0x89d32be0L), tole(0x10da7a5aL), tole(0x67dd4accL), 
tole(0xf9b9df6fL), tole(0x8ebeeff9L), tole(0x17b7be43L), tole(0x60b08ed5L), 
tole(0xd6d6a3e8L), tole(0xa1d1937eL), tole(0x38d8c2c4L), tole(0x4fdff252L), 
tole(0xd1bb67f1L), tole(0xa6bc5767L), tole(0x3fb506ddL), tole(0x48b2364bL), 
tole(0xd80d2bdaL), tole(0xaf0a1b4cL), tole(0x36034af6L), tole(0x41047a60L), 
tole(0xdf60efc3L), tole(0xa867df55L), tole(0x316e8eefL), tole(0x4669be79L), 
tole(0xcb61b38cL), tole(0xbc66831aL), tole(0x256fd2a0L), tole(0x5268e236L), 
tole(0xcc0c7795L), tole(0xbb0b4703L), tole(0x220216b9L), tole(0x5505262fL), 
tole(0xc5ba3bbeL), tole(0xb2bd0b28L), tole(0x2bb45a92L), tole(0x5cb36a04L), 
tole(0xc2d7ffa7L), tole(0xb5d0cf31L), tole(0x2cd99e8bL), tole(0x5bdeae1dL), 
tole(0x9b64c2b0L), tole(0xec63f226L), tole(0x756aa39cL), tole(0x026d930aL), 
tole(0x9c0906a9L), tole(0xeb0e363fL), tole(0x72076785L), tole(0x05005713L), 
tole(0x95bf4a82L), tole(0xe2b87a14L), tole(0x7bb12baeL), tole(0x0cb61b38L), 
tole(0x92d28e9bL), tole(0xe5d5be0dL), tole(0x7cdcefb7L), tole(0x0bdbdf21L), 
tole(0x86d3d2d4L), tole(0xf1d4e242L), tole(0x68ddb3f8L), tole(0x1fda836eL), 
tole(0x81be16cdL), tole(0xf6b9265bL), tole(0x6fb077e1L), tole(0x18b74777L), 
tole(0x88085ae6L), tole(0xff0f6a70L), tole(0x66063bcaL), tole(0x11010b5cL), 
tole(0x8f659effL), tole(0xf862ae69L), tole(0x616bffd3L), tole(0x166ccf45L), 
tole(0xa00ae278L), tole(0xd70dd2eeL), tole(0x4e048354L), tole(0x3903b3c2L), 
tole(0xa7672661L), tole(0xd06016f7L), tole(0x4969474dL), tole(0x3e6e77dbL), 
tole(0xaed16a4aL), tole(0xd9d65adcL), tole(0x40df0b66L), tole(0x37d83bf0L), 
tole(0xa9bcae53L), tole(0xdebb9ec5L), tole(0x47b2cf7fL), tole(0x30b5ffe9L), 
tole(0xbdbdf21cL), tole(0xcabac28aL), tole(0x53b39330L), tole(0x24b4a3a6L), 
tole(0xbad03605L), tole(0xcdd70693L), tole(0x54de5729L), tole(0x23d967bfL), 
tole(0xb3667a2eL), tole(0xc4614ab8L), tole(0x5d681b02L), tole(0x2a6f2b94L), 
tole(0xb40bbe37L), tole(0xc30c8ea1L), tole(0x5a05df1bL), tole(0x2d02ef8dL)},
{
tole(0x00000000L), tole(0x191b3141L), tole(0x32366282L), tole(0x2b2d53c3L), 
tole(0x646cc504L), tole(0x7d77f445L), tole(0x565aa786L), tole(0x4f4196c7L), 
tole(0xc8d98a08L), tole(0xd1c2bb49L), tole(0xfaefe88aL), tole(0xe3f4d9cbL), 
tole(0xacb54f0cL), tole(0xb5ae7e4dL), tole(0x9e832d8eL), tole(0x87981ccfL), 
tole(0x4ac21251L), tole(0x53d92310L), tole(0x78f470d3L), tole(0x61ef4192L), 
tole(0x2eaed755L), tole(0x37b5e614L), tole(0x1c98b5d7L), tole(0x05838496L), 
tole(0x821b9859L), tole(0x9b00a918L), tole(0xb02dfadbL), tole(0xa936cb9aL), 
tole(0xe6775d5dL), tole(0xff6c6c1cL), tole(0xd4413fdfL), tole(0xcd5a0e9eL), 
tole(0x958424a2L), tole(0x8c9f15e3L), tole(0xa7b24620L), tole(0xbea97761L), 
tole(0xf1e8e1a6L), tole(0xe8f3d0e7L), tole(0xc3de8324L), tole(0xdac5b265L), 
tole(0x5d5daeaaL), tole(0x44469febL), tole(0x6f6bcc28L), tole(0x7670fd69L), 
tole(0x39316baeL), tole(0x202a5aefL), tole(0x0b07092cL), tole(0x121c386dL), 
tole(0xdf4636f3L), tole(0xc65d07b2L), tole(0xed705471L), tole(0xf46b6530L), 
tole(0xbb2af3f7L), tole(0xa231c2b6L), tole(0x891c9175L), tole(0x9007a034L), 
tole(0x179fbcfbL), tole(0x0e848dbaL), tole(0x25a9de79L), tole(0x3cb2ef38L), 
tole(0x73f379ffL), tole(0x6ae848beL), tole(0x41c51b7dL), tole(0x58de2a3cL), 
tole(0xf0794f05L), tole(0xe9627e44L), tole(0xc24f2d87L), tole(0xdb541cc6L), 
tole(0x94158a01L), tole(0x8d0ebb40L), tole(0xa623e883L), tole(0xbf38d9c2L), 
tole(0x38a0c50dL), tole(0x21bbf44cL), tole(0x0a96a78fL), tole(0x138d96ceL), 
tole(0x5ccc0009L), tole(0x45d73148L), tole(0x6efa628bL), tole(0x77e153caL), 
tole(0xbabb5d54L), tole(0xa3a06c15L), tole(0x888d3fd6L), tole(0x91960e97L), 
tole(0xded79850L), tole(0xc7cca911L), tole(0xece1fad2L), tole(0xf5facb93L), 
tole(0x7262d75cL), tole(0x6b79e61dL), tole(0x4054b5deL), tole(0x594f849fL), 
tole(0x160e1258L), tole(0x0f152319L), tole(0x243870daL), tole(0x3d23419bL), 
tole(0x65fd6ba7L), tole(0x7ce65ae6L), tole(0x57cb0925L), tole(0x4ed03864L), 
tole(0x0191aea3L), tole(0x188a9fe2L), tole(0x33a7cc21L), tole(0x2abcfd60L), 
tole(0xad24e1afL), tole(0xb43fd0eeL), tole(0x9f12832dL), tole(0x8609b26cL), 
tole(0xc94824abL), tole(0xd05315eaL), tole(0xfb7e4629L), tole(0xe2657768L), 
tole(0x2f3f79f6L), tole(0x362448b7L), tole(0x1d091b74L), tole(0x04122a35L), 
tole(0x4b53bcf2L), tole(0x52488db3L), tole(0x7965de70L), tole(0x607eef31L), 
tole(0xe7e6f3feL), tole(0xfefdc2bfL), tole(0xd5d0917cL), tole(0xcccba03dL), 
tole(0x838a36faL), tole(0x9a9107bbL), tole(0xb1bc5478L), tole(0xa8a76539L), 
tole(0x3b83984bL), tole(0x2298a90aL), tole(0x09b5fac9L), tole(0x10aecb88L), 
tole(0x5fef5d4fL), tole(0x46f46c0eL), tole(0x6dd93fcdL), tole(0x74c20e8cL), 
tole(0xf35a1243L), tole(0xea412302L), tole(0xc16c70c1L), tole(0xd8774180L), 
tole(0x9736d747L), tole(0x8e2de606L), tole(0xa500b5c5L), tole(0xbc1b8484L), 
tole(0x71418a1aL), tole(0x685abb5bL), tole(0x4377e898L), tole(0x5a6cd9d9L), 
tole(0x152d4f1eL), tole(0x0c367e5fL), tole(0x271b2d9cL), tole(0x3e001cddL), 
tole(0xb9980012L), tole(0xa0833153L), tole(0x8bae6290L), tole(0x92b553d1L), 
tole(0xddf4c516L), tole(0xc4eff457L), tole(0xefc2a794L), tole(0xf6d996d5L), 
tole(0xae07bce9L), tole(0xb71c8da8L), tole(0x9c31de6bL), tole(0x852aef2aL), 
tole(0xca6b79edL), tole(0xd37048acL), tole(0xf85d1b6fL), tole(0xe1462a2eL), 
tole(0x66de36e1L), tole(0x7fc507a0L), tole(0x54e85463L), tole(0x4df36522L), 
tole(0x02b2f3e5L), tole(0x1ba9c2a4L), tole(0x30849167L), tole(0x299fa026L), 
tole(0xe4c5aeb8L), tole(0xfdde9ff9L), tole(0xd6f3cc3aL), tole(0xcfe8fd7bL), 
tole(0x80a96bbcL), tole(0x99b25afdL), tole(0xb29f093eL), tole(0xab84387fL), 
tole(0x2c1c24b0L), tole(0x350715f1L), tole(0x1e2a4632L), tole(0x07317773L), 
tole(0x4870e1b4L), tole(0x516bd0f5L), tole(0x7a468336L), tole(0x635db277L), 
tole(0xcbfad74eL), tole(0xd2e1e60fL), tole(0xf9ccb5ccL), tole(0xe0d7848dL), 
tole(0xaf96124aL), tole(0xb68d230bL), tole(0x9da070c8L), tole(0x84bb4189L), 
tole(0x03235d46L), tole(0x1a386c07L), tole(0x31153fc4L), tole(0x280e0e85L), 
tole(0x674f9842L), tole(0x7e54a903L), tole(0x5579fac0L), tole(0x4c62cb81L), 
tole(0x8138c51fL), tole(0x9823f45eL), tole(0xb30ea79dL), tole(0xaa1596dcL), 
tole(0xe554001bL), tole(0xfc4f315aL), tole(0xd7626299L), tole(0xce7953d8L), 
tole(0x49e14f17L), tole(0x50fa7e56L), tole(0x7bd72d95L), tole(0x62cc1cd4L), 
tole(0x2d8d8a13L), tole(0x3496bb52L), tole(0x1fbbe891L), tole(0x06a0d9d0L), 
tole(0x5e7ef3ecL), tole(0x4765c2adL), tole(0x6c48916eL), tole(0x7553a02fL), 
tole(0x3a1236e8L), tole(0x230907a9L), tole(0x0824546aL), tole(0x113f652bL), 
tole(0x96a779e4L), tole(0x8fbc48a5L), tole(0xa4911b66L), tole(0xbd8a2a27L), 
tole(0xf2cbbce0L), tole(0xebd08da1L), tole(0xc0fdde62L), tole(0xd9e6ef23L), 
tole(0x14bce1bdL), tole(0x0da7d0fcL), tole(0x268a833fL), tole(0x3f91b27eL), 
tole(0x70d024b9L), tole(0x69cb15f8L), tole(0x42e6463bL), tole(0x5bfd777aL), 
tole(0xdc656bb5L), tole(0xc57e5af4L), tole(0xee530937L), tole(0xf7483876L), 
tole(0xb809aeb1L), tole(0xa1129ff0L), tole(0x8a3fcc33L), tole(0x9324fd72L)},
{
tole(0x00000000L), tole(0x01c26a37L), tole(0x0384d46eL), tole(0x0246be59L), 
tole(0x0709a8dcL), tole(0x06cbc2ebL), tole(0x048d7cb2L), tole(0x054f1685L), 
tole(0x0e1351b8L), tole(0x0fd13b8fL), tole(0x0d9785d6L), tole(0x0c55efe1L), 
tole(0x091af964L), tole(0x08d89353L), tole(0x0a9e2d0aL), tole(0x0b5c473dL), 
tole(0x1c26a370L), tole(0x1de4c947L), tole(0x1fa2771eL), tole(0x1e601d29L), 
tole(0x1b2f0bacL), tole(0x1aed619bL), tole(0x18abdfc2L), tole(0x1969b5f5L), 
tole(0x1235f2c8L), tole(0x13f798ffL), tole(0x11b126a6L), tole(0x10734c91L), 
tole(0x153c5a14L), tole(0x14fe3023L), tole(0x16b88e7aL), tole(0x177ae44dL), 
tole(0x384d46e0L), tole(0x398f2cd7L), tole(0x3bc9928eL), tole(0x3a0bf8b9L), 
tole(0x3f44ee3cL), tole(0x3e86840bL), tole(0x3cc03a52L), tole(0x3d025065L), 
tole(0x365e1758L), tole(0x379c7d6fL), tole(0x35dac336L), tole(0x3418a901L), 
tole(0x3157bf84L), tole(0x3095d5b3L), tole(0x32d36beaL), tole(0x331101ddL), 
tole(0x246be590L), tole(0x25a98fa7L), tole(0x27ef31feL), tole(0x262d5bc9L), 
tole(0x23624d4cL), tole(0x22a0277bL), tole(0x20e69922L), tole(0x2124f315L), 
tole(0x2a78b428L), tole(0x2bbade1fL), tole(0x29fc6046L), tole(0x283e0a71L), 
tole(0x2d711cf4L), tole(0x2cb376c3L), tole(0x2ef5c89aL), tole(0x2f37a2adL), 
tole(0x709a8dc0L), tole(0x7158e7f7L), tole(0x731e59aeL), tole(0x72dc3399L), 
tole(0x7793251cL), tole(0x76514f2bL), tole(0x7417f172L), tole(0x75d59b45L), 
tole(0x7e89dc78L), tole(0x7f4bb64fL), tole(0x7d0d0816L), tole(0x7ccf6221L), 
tole(0x798074a4L), tole(0x78421e93L), tole(0x7a04a0caL), tole(0x7bc6cafdL), 
tole(0x6cbc2eb0L), tole(0x6d7e4487L), tole(0x6f38fadeL), tole(0x6efa90e9L), 
tole(0x6bb5866cL), tole(0x6a77ec5bL), tole(0x68315202L), tole(0x69f33835L), 
tole(0x62af7f08L), tole(0x636d153fL), tole(0x612bab66L), tole(0x60e9c151L), 
tole(0x65a6d7d4L), tole(0x6464bde3L), tole(0x662203baL), tole(0x67e0698dL), 
tole(0x48d7cb20L), tole(0x4915a117L), tole(0x4b531f4eL), tole(0x4a917579L), 
tole(0x4fde63fcL), tole(0x4e1c09cbL), tole(0x4c5ab792L), tole(0x4d98dda5L), 
tole(0x46c49a98L), tole(0x4706f0afL), tole(0x45404ef6L), tole(0x448224c1L), 
tole(0x41cd3244L), tole(0x400f5873L), tole(0x4249e62aL), tole(0x438b8c1dL), 
tole(0x54f16850L), tole(0x55330267L), tole(0x5775bc3eL), tole(0x56b7d609L), 
tole(0x53f8c08cL), tole(0x523aaabbL), tole(0x507c14e2L), tole(0x51be7ed5L), 
tole(0x5ae239e8L), tole(0x5b2053dfL), tole(0x5966ed86L), tole(0x58a487b1L), 
tole(0x5deb9134L), tole(0x5c29fb03L), tole(0x5e6f455aL), tole(0x5fad2f6dL), 
tole(0xe1351b80L), tole(0xe0f771b7L), tole(0xe2b1cfeeL), tole(0xe373a5d9L), 
tole(0xe63cb35cL), tole(0xe7fed96bL), tole(0xe5b86732L), tole(0xe47a0d05L), 
tole(0xef264a38L), tole(0xeee4200fL), tole(0xeca29e56L), tole(0xed60f461L), 
tole(0xe82fe2e4L), tole(0xe9ed88d3L), tole(0xebab368aL), tole(0xea695cbdL), 
tole(0xfd13b8f0L), tole(0xfcd1d2c7L), tole(0xfe976c9eL), tole(0xff5506a9L), 
tole(0xfa1a102cL), tole(0xfbd87a1bL), tole(0xf99ec442L), tole(0xf85cae75L), 
tole(0xf300e948L), tole(0xf2c2837fL), tole(0xf0843d26L), tole(0xf1465711L), 
tole(0xf4094194L), tole(0xf5cb2ba3L), tole(0xf78d95faL), tole(0xf64fffcdL), 
tole(0xd9785d60L), tole(0xd8ba3757L), tole(0xdafc890eL), tole(0xdb3ee339L), 
tole(0xde71f5bcL), tole(0xdfb39f8bL), tole(0xddf521d2L), tole(0xdc374be5L), 
tole(0xd76b0cd8L), tole(0xd6a966efL), tole(0xd4efd8b6L), tole(0xd52db281L), 
tole(0xd062a404L), tole(0xd1a0ce33L), tole(0xd3e6706aL), tole(0xd2241a5dL), 
tole(0xc55efe10L), tole(0xc49c9427L), tole(0xc6da2a7eL), tole(0xc7184049L), 
tole(0xc25756ccL), tole(0xc3953cfbL), tole(0xc1d382a2L), tole(0xc011e895L), 
tole(0xcb4dafa8L), tole(0xca8fc59fL), tole(0xc8c97bc6L), tole(0xc90b11f1L), 
tole(0xcc440774L), tole(0xcd866d43L), tole(0xcfc0d31aL), tole(0xce02b92dL), 
tole(0x91af9640L), tole(0x906dfc77L), tole(0x922b422eL), tole(0x93e92819L), 
tole(0x96a63e9cL), tole(0x976454abL), tole(0x9522eaf2L), tole(0x94e080c5L), 
tole(0x9fbcc7f8L), tole(0x9e7eadcfL), tole(0x9c381396L), tole(0x9dfa79a1L), 
tole(0x98b56f24L), tole(0x99770513L), tole(0x9b31bb4aL), tole(0x9af3d17dL), 
tole(0x8d893530L), tole(0x8c4b5f07L), tole(0x8e0de15eL), tole(0x8fcf8b69L), 
tole(0x8a809decL), tole(0x8b42f7dbL), tole(0x89044982L), tole(0x88c623b5L), 
tole(0x839a6488L), tole(0x82580ebfL), tole(0x801eb0e6L), tole(0x81dcdad1L), 
tole(0x8493cc54L), tole(0x8551a663L), tole(0x8717183aL), tole(0x86d5720dL), 
tole(0xa9e2d0a0L), tole(0xa820ba97L), tole(0xaa6604ceL), tole(0xaba46ef9L), 
tole(0xaeeb787cL), tole(0xaf29124bL), tole(0xad6fac12L), tole(0xacadc625L), 
tole(0xa7f18118L), tole(0xa633eb2fL), tole(0xa4755576L), tole(0xa5b73f41L), 
tole(0xa0f829c4L), tole(0xa13a43f3L), tole(0xa37cfdaaL), tole(0xa2be979dL), 
tole(0xb5c473d0L), tole(0xb40619e7L), tole(0xb640a7beL), tole(0xb782cd89L), 
tole(0xb2cddb0cL), tole(0xb30fb13bL), tole(0xb1490f62L), tole(0xb08b6555L), 
tole(0xbbd72268L), tole(0xba15485fL), tole(0xb853f606L), tole(0xb9919c31L), 
tole(0xbcde8ab4L), tole(0xbd1ce083L), tole(0xbf5a5edaL), tole(0xbe9834edL)},
{
tole(0x00000000L), tole(0xb8bc6765L), tole(0xaa09c88bL), tole(0x12b5afeeL), 
tole(0x8f629757L), tole(0x37def032L), tole(0x256b5fdcL), tole(0x9dd738b9L), 
tole(0xc5b428efL), tole(0x7d084f8aL), tole(0x6fbde064L), tole(0xd7018701L), 
tole(0x4ad6bfb8L), tole(0xf26ad8ddL), tole(0xe0df7733L), tole(0x58631056L), 
tole(0x5019579fL), tole(0xe8a530faL), tole(0xfa109f14L), tole(0x42acf871L), 
tole(0xdf7bc0c8L), tole(0x67c7a7adL), tole(0x75720843L), tole(0xcdce6f26L), 
tole(0x95ad7f70L), tole(0x2d111815L), tole(0x3fa4b7fbL), tole(0x8718d09eL), 
tole(0x1acfe827L), tole(0xa2738f42L), tole(0xb0c620acL), tole(0x087a47c9L), 
tole(0xa032af3eL), tole(0x188ec85bL), tole(0x0a3b67b5L), tole(0xb28700d0L), 
tole(0x2f503869L), tole(0x97ec5f0cL), tole(0x8559f0e2L), tole(0x3de59787L), 
tole(0x658687d1L), tole(0xdd3ae0b4L), tole(0xcf8f4f5aL), tole(0x7733283fL), 
tole(0xeae41086L), tole(0x525877e3L), tole(0x40edd80dL), tole(0xf851bf68L), 
tole(0xf02bf8a1L), tole(0x48979fc4L), tole(0x5a22302aL), tole(0xe29e574fL), 
tole(0x7f496ff6L), tole(0xc7f50893L), tole(0xd540a77dL), tole(0x6dfcc018L), 
tole(0x359fd04eL), tole(0x8d23b72bL), tole(0x9f9618c5L), tole(0x272a7fa0L), 
tole(0xbafd4719L), tole(0x0241207cL), tole(0x10f48f92L), tole(0xa848e8f7L), 
tole(0x9b14583dL), tole(0x23a83f58L), tole(0x311d90b6L), tole(0x89a1f7d3L), 
tole(0x1476cf6aL), tole(0xaccaa80fL), tole(0xbe7f07e1L), tole(0x06c36084L), 
tole(0x5ea070d2L), tole(0xe61c17b7L), tole(0xf4a9b859L), tole(0x4c15df3cL), 
tole(0xd1c2e785L), tole(0x697e80e0L), tole(0x7bcb2f0eL), tole(0xc377486bL), 
tole(0xcb0d0fa2L), tole(0x73b168c7L), tole(0x6104c729L), tole(0xd9b8a04cL), 
tole(0x446f98f5L), tole(0xfcd3ff90L), tole(0xee66507eL), tole(0x56da371bL), 
tole(0x0eb9274dL), tole(0xb6054028L), tole(0xa4b0efc6L), tole(0x1c0c88a3L), 
tole(0x81dbb01aL), tole(0x3967d77fL), tole(0x2bd27891L), tole(0x936e1ff4L), 
tole(0x3b26f703L), tole(0x839a9066L), tole(0x912f3f88L), tole(0x299358edL), 
tole(0xb4446054L), tole(0x0cf80731L), tole(0x1e4da8dfL), tole(0xa6f1cfbaL), 
tole(0xfe92dfecL), tole(0x462eb889L), tole(0x549b1767L), tole(0xec277002L), 
tole(0x71f048bbL), tole(0xc94c2fdeL), tole(0xdbf98030L), tole(0x6345e755L), 
tole(0x6b3fa09cL), tole(0xd383c7f9L), tole(0xc1366817L), tole(0x798a0f72L), 
tole(0xe45d37cbL), tole(0x5ce150aeL), tole(0x4e54ff40L), tole(0xf6e89825L), 
tole(0xae8b8873L), tole(0x1637ef16L), tole(0x048240f8L), tole(0xbc3e279dL), 
tole(0x21e91f24L), tole(0x99557841L), tole(0x8be0d7afL), tole(0x335cb0caL), 
tole(0xed59b63bL), tole(0x55e5d15eL), tole(0x47507eb0L), tole(0xffec19d5L), 
tole(0x623b216cL), tole(0xda874609L), tole(0xc832e9e7L), tole(0x708e8e82L), 
tole(0x28ed9ed4L), tole(0x9051f9b1L), tole(0x82e4565fL), tole(0x3a58313aL), 
tole(0xa78f0983L), tole(0x1f336ee6L), tole(0x0d86c108L), tole(0xb53aa66dL), 
tole(0xbd40e1a4L), tole(0x05fc86c1L), tole(0x1749292fL), tole(0xaff54e4aL), 
tole(0x322276f3L), tole(0x8a9e1196L), tole(0x982bbe78L), tole(0x2097d91dL), 
tole(0x78f4c94bL), tole(0xc048ae2eL), tole(0xd2fd01c0L), tole(0x6a4166a5L), 
tole(0xf7965e1cL), tole(0x4f2a3979L), tole(0x5d9f9697L), tole(0xe523f1f2L), 
tole(0x4d6b1905L), tole(0xf5d77e60L), tole(0xe762d18eL), tole(0x5fdeb6ebL), 
tole(0xc2098e52L), tole(0x7ab5e937L), tole(0x680046d9L), tole(0xd0bc21bcL), 
tole(0x88df31eaL), tole(0x3063568fL), tole(0x22d6f961L), tole(0x9a6a9e04L), 
tole(0x07bda6bdL), tole(0xbf01c1d8L), tole(0xadb46e36L), tole(0x15080953L), 
tole(0x1d724e9aL), tole(0xa5ce29ffL), tole(0xb77b8611L), tole(0x0fc7e174L), 
tole(0x9210d9cdL), tole(0x2aacbea8L), tole(0x38191146L), tole(0x80a57623L), 
tole(0xd8c66675L), tole(0x607a0110L), tole(0x72cfaefeL), tole(0xca73c99bL), 
tole(0x57a4f122L), tole(0xef189647L), tole(0xfdad39a9L), tole(0x45115eccL), 
tole(0x764dee06L), tole(0xcef18963L), tole(0xdc44268dL), tole(0x64f841e8L), 
tole(0xf92f7951L), tole(0x41931e34L), tole(0x5326b1daL), tole(0xeb9ad6bfL), 
tole(0xb3f9c6e9L), tole(0x0b45a18cL), tole(0x19f00e62L), tole(0xa14c6907L), 
tole(0x3c9b51beL), tole(0x842736dbL), tole(0x96929935L), tole(0x2e2efe50L), 
tole(0x2654b999L), tole(0x9ee8defcL), tole(0x8c5d7112L), tole(0x34e11677L), 
tole(0xa9362eceL), tole(0x118a49abL), tole(0x033fe645L), tole(0xbb838120L), 
tole(0xe3e09176L), tole(0x5b5cf613L), tole(0x49e959fdL), tole(0xf1553e98L), 
tole(0x6c820621L), tole(0xd43e6144L), tole(0xc68bceaaL), tole(0x7e37a9cfL), 
tole(0xd67f4138L), tole(0x6ec3265dL), tole(0x7c7689b3L), tole(0xc4caeed6L), 
tole(0x591dd66fL), tole(0xe1a1b10aL), tole(0xf3141ee4L), tole(0x4ba87981L), 
tole(0x13cb69d7L), tole(0xab770eb2L), tole(0xb9c2a15cL), tole(0x017ec639L), 
tole(0x9ca9fe80L), tole(0x241599e5L), tole(0x36a0360bL), tole(0x8e1c516eL), 
tole(0x866616a7L), tole(0x3eda71c2L), tole(0x2c6fde2cL), tole(0x94d3b949L), 
tole(0x090481f0L), tole(0xb1b8e695L), tole(0xa30d497bL), tole(0x1bb12e1eL), 
tole(0x43d23e48L), tole(0xfb6e592dL), tole(0xe9dbf6c3L), tole(0x516791a6L), 
tole(0xccb0a91fL), tole(0x740cce7aL), tole(0x66b96194L), tole(0xde0506f1L)},
{
tole(0x00000000L), tole(0x3d6029b0L), tole(0x7ac05360L), tole(0x47a07ad0L), 
tole(0xf580a6c0L), tole(0xc8e08f70L), tole(0x8f40f5a0L), tole(0xb220dc10L), 
tole(0x30704bc1L), tole(0x0d106271L), tole(0x4ab018a1L), tole(0x77d03111L), 
tole(0xc5f0ed01L), tole(0xf890c4b1L), tole(0xbf30be61L), tole(0x825097d1L), 
tole(0x60e09782L), tole(0x5d80be32L), tole(0x1a20c4e2L), tole(0x2740ed52L), 
tole(0x95603142L), tole(0xa80018f2L), tole(0xefa06222L), tole(0xd2c04b92L), 
tole(0x5090dc43L), tole(0x6df0f5f3L), tole(0x2a508f23L), tole(0x1730a693L), 
tole(0xa5107a83L), tole(0x98705333L), tole(0xdfd029e3L), tole(0xe2b00053L), 
tole(0xc1c12f04L), tole(0xfca106b4L), tole(0xbb017c64L), tole(0x866155d4L), 
tole(0x344189c4L), tole(0x0921a074L), tole(0x4e81daa4L), tole(0x73e1f314L), 
tole(0xf1b164c5L), tole(0xccd14d75L), tole(0x8b7137a5L), tole(0xb6111e15L), 
tole(0x0431c205L), tole(0x3951ebb5L), tole(0x7ef19165L), tole(0x4391b8d5L), 
tole(0xa121b886L), tole(0x9c419136L), tole(0xdbe1ebe6L), tole(0xe681c256L), 
tole(0x54a11e46L), tole(0x69c137f6L), tole(0x2e614d26L), tole(0x13016496L), 
tole(0x9151f347L), tole(0xac31daf7L), tole(0xeb91a027L), tole(0xd6f18997L), 
tole(0x64d15587L), tole(0x59b17c37L), tole(0x1e1106e7L), tole(0x23712f57L), 
tole(0x58f35849L), tole(0x659371f9L), tole(0x22330b29L), tole(0x1f532299L), 
tole(0xad73fe89L), tole(0x9013d739L), tole(0xd7b3ade9L), tole(0xead38459L), 
tole(0x68831388L), tole(0x55e33a38L), tole(0x124340e8L), tole(0x2f236958L), 
tole(0x9d03b548L), tole(0xa0639cf8L), tole(0xe7c3e628L), tole(0xdaa3cf98L), 
tole(0x3813cfcbL), tole(0x0573e67bL), tole(0x42d39cabL), tole(0x7fb3b51bL), 
tole(0xcd93690bL), tole(0xf0f340bbL), tole(0xb7533a6bL), tole(0x8a3313dbL), 
tole(0x0863840aL), tole(0x3503adbaL), tole(0x72a3d76aL), tole(0x4fc3fedaL), 
tole(0xfde322caL), tole(0xc0830b7aL), tole(0x872371aaL), tole(0xba43581aL), 
tole(0x9932774dL), tole(0xa4525efdL), tole(0xe3f2242dL), tole(0xde920d9dL), 
tole(0x6cb2d18dL), tole(0x51d2f83dL), tole(0x167282edL), tole(0x2b12ab5dL), 
tole(0xa9423c8cL), tole(0x9422153cL), tole(0xd3826fecL), tole(0xeee2465cL), 
tole(0x5cc29a4cL), tole(0x61a2b3fcL), tole(0x2602c92cL), tole(0x1b62e09cL), 
tole(0xf9d2e0cfL), tole(0xc4b2c97fL), tole(0x8312b3afL), tole(0xbe729a1fL), 
tole(0x0c52460fL), tole(0x31326fbfL), tole(0x7692156fL), tole(0x4bf23cdfL), 
tole(0xc9a2ab0eL), tole(0xf4c282beL), tole(0xb362f86eL), tole(0x8e02d1deL), 
tole(0x3c220dceL), tole(0x0142247eL), tole(0x46e25eaeL), tole(0x7b82771eL), 
tole(0xb1e6b092L), tole(0x8c869922L), tole(0xcb26e3f2L), tole(0xf646ca42L), 
tole(0x44661652L), tole(0x79063fe2L), tole(0x3ea64532L), tole(0x03c66c82L), 
tole(0x8196fb53L), tole(0xbcf6d2e3L), tole(0xfb56a833L), tole(0xc6368183L), 
tole(0x74165d93L), tole(0x49767423L), tole(0x0ed60ef3L), tole(0x33b62743L), 
tole(0xd1062710L), tole(0xec660ea0L), tole(0xabc67470L), tole(0x96a65dc0L), 
tole(0x248681d0L), tole(0x19e6a860L), tole(0x5e46d2b0L), tole(0x6326fb00L), 
tole(0xe1766cd1L), tole(0xdc164561L), tole(0x9bb63fb1L), tole(0xa6d61601L), 
tole(0x14f6ca11L), tole(0x2996e3a1L), tole(0x6e369971L), tole(0x5356b0c1L), 
tole(0x70279f96L), tole(0x4d47b626L), tole(0x0ae7ccf6L), tole(0x3787e546L), 
tole(0x85a73956L), tole(0xb8c710e6L), tole(0xff676a36L), tole(0xc2074386L), 
tole(0x4057d457L), tole(0x7d37fde7L), tole(0x3a978737L), tole(0x07f7ae87L), 
tole(0xb5d77297L), tole(0x88b75b27L), tole(0xcf1721f7L), tole(0xf2770847L), 
tole(0x10c70814L), tole(0x2da721a4L), tole(0x6a075b74L), tole(0x576772c4L), 
tole(0xe547aed4L), tole(0xd8278764L), tole(0x9f87fdb4L), tole(0xa2e7d404L), 
tole(0x20b743d5L), tole(0x1dd76a65L), tole(0x5a7710b5L), tole(0x67173905L), 
tole(0xd537e515L), tole(0xe857cca5L), tole(0xaff7b675L), tole(0x92979fc5L), 
tole(0xe915e8dbL), tole(0xd475c16bL), tole(0x93d5bbbbL), tole(0xaeb5920bL), 
tole(0x1c954e1bL), tole(0x21f567abL), tole(0x66551d7bL), tole(0x5b3534cbL), 
tole(0xd965a31aL), tole(0xe4058aaaL), tole(0xa3a5f07aL), tole(0x9ec5d9caL), 
tole(0x2ce505daL), tole(0x11852c6aL), tole(0x562556baL), tole(0x6b457f0aL), 
tole(0x89f57f59L), tole(0xb49556e9L), tole(0xf3352c39L), tole(0xce550589L), 
tole(0x7c75d999L), tole(0x4115f029L), tole(0x06b58af9L), tole(0x3bd5a349L), 
tole(0xb9853498L), tole(0x84e51d28L), tole(0xc34567f8L), tole(0xfe254e48L), 
tole(0x4c059258L), tole(0x7165bbe8L), tole(0x36c5c138L), tole(0x0ba5e888L), 
tole(0x28d4c7dfL), tole(0x15b4ee6fL), tole(0x521494bfL), tole(0x6f74bd0fL), 
tole(0xdd54611fL), tole(0xe03448afL), tole(0xa794327fL), tole(0x9af41bcfL), 
tole(0x18a48c1eL), tole(0x25c4a5aeL), tole(0x6264df7eL), tole(0x5f04f6ceL), 
tole(0xed242adeL), tole(0xd044036eL), tole(0x97e479beL), tole(0xaa84500eL), 
tole(0x4834505dL), tole(0x755479edL), tole(0x32f4033dL), tole(0x0f942a8dL), 
tole(0xbdb4f69dL), tole(0x80d4df2dL), tole(0xc774a5fdL), tole(0xfa148c4dL), 
tole(0x78441b9cL), tole(0x4524322cL), tole(0x028448fcL), tole(0x3fe4614cL), 
tole(0x8dc4bd5cL), tole(0xb0a494ecL), tole(0xf704ee3cL), tole(0xca64c78cL)},
{
tole(0x00000000L), tole(0xcb5cd3a5L), tole(0x4dc8a10bL), tole(0x869472aeL), 
tole(0x9b914216L), tole(0x50cd91b3L), tole(0xd659e31dL), tole(0x1d0530b8L), 
tole(0xec53826dL), tole(0x270f51c8L), tole(0xa19b2366L), tole(0x6ac7f0c3L), 
tole(0x77c2c07bL), tole(0xbc9e13deL), tole(0x3a0a6170L), tole(0xf156b2d5L), 
tole(0x03d6029bL), tole(0xc88ad13eL), tole(0x4e1ea390L), tole(0x85427035L), 
tole(0x9847408dL), tole(0x531b9328L), tole(0xd58fe186L), tole(0x1ed33223L), 
tole(0xef8580f6L), tole(0x24d95353L), tole(0xa24d21fdL), tole(0x6911f258L), 
tole(0x7414c2e0L), tole(0xbf481145L), tole(0x39dc63ebL), tole(0xf280b04eL), 
tole(0x07ac0536L), tole(0xccf0d693L), tole(0x4a64a43dL), tole(0x81387798L), 
tole(0x9c3d4720L), tole(0x57619485L), tole(0xd1f5e62bL), tole(0x1aa9358eL), 
tole(0xebff875bL), tole(0x20a354feL), tole(0xa6372650L), tole(0x6d6bf5f5L), 
tole(0x706ec54dL), tole(0xbb3216e8L), tole(0x3da66446L), tole(0xf6fab7e3L), 
tole(0x047a07adL), tole(0xcf26d408L), tole(0x49b2a6a6L), tole(0x82ee7503L), 
tole(0x9feb45bbL), tole(0x54b7961eL), tole(0xd223e4b0L), tole(0x197f3715L), 
tole(0xe82985c0L), tole(0x23755665L), tole(0xa5e124cbL), tole(0x6ebdf76eL), 
tole(0x73b8c7d6L), tole(0xb8e41473L), tole(0x3e7066ddL), tole(0xf52cb578L), 
tole(0x0f580a6cL), tole(0xc404d9c9L), tole(0x4290ab67L), tole(0x89cc78c2L), 
tole(0x94c9487aL), tole(0x5f959bdfL), tole(0xd901e971L), tole(0x125d3ad4L), 
tole(0xe30b8801L), tole(0x28575ba4L), tole(0xaec3290aL), tole(0x659ffaafL), 
tole(0x789aca17L), tole(0xb3c619b2L), tole(0x35526b1cL), tole(0xfe0eb8b9L), 
tole(0x0c8e08f7L), tole(0xc7d2db52L), tole(0x4146a9fcL), tole(0x8a1a7a59L), 
tole(0x971f4ae1L), tole(0x5c439944L), tole(0xdad7ebeaL), tole(0x118b384fL), 
tole(0xe0dd8a9aL), tole(0x2b81593fL), tole(0xad152b91L), tole(0x6649f834L), 
tole(0x7b4cc88cL), tole(0xb0101b29L), tole(0x36846987L), tole(0xfdd8ba22L), 
tole(0x08f40f5aL), tole(0xc3a8dcffL), tole(0x453cae51L), tole(0x8e607df4L), 
tole(0x93654d4cL), tole(0x58399ee9L), tole(0xdeadec47L), tole(0x15f13fe2L), 
tole(0xe4a78d37L), tole(0x2ffb5e92L), tole(0xa96f2c3cL), tole(0x6233ff99L), 
tole(0x7f36cf21L), tole(0xb46a1c84L), tole(0x32fe6e2aL), tole(0xf9a2bd8fL), 
tole(0x0b220dc1L), tole(0xc07ede64L), tole(0x46eaaccaL), tole(0x8db67f6fL), 
tole(0x90b34fd7L), tole(0x5bef9c72L), tole(0xdd7beedcL), tole(0x16273d79L), 
tole(0xe7718facL), tole(0x2c2d5c09L), tole(0xaab92ea7L), tole(0x61e5fd02L), 
tole(0x7ce0cdbaL), tole(0xb7bc1e1fL), tole(0x31286cb1L), tole(0xfa74bf14L), 
tole(0x1eb014d8L), tole(0xd5ecc77dL), tole(0x5378b5d3L), tole(0x98246676L), 
tole(0x852156ceL), tole(0x4e7d856bL), tole(0xc8e9f7c5L), tole(0x03b52460L), 
tole(0xf2e396b5L), tole(0x39bf4510L), tole(0xbf2b37beL), tole(0x7477e41bL), 
tole(0x6972d4a3L), tole(0xa22e0706L), tole(0x24ba75a8L), tole(0xefe6a60dL), 
tole(0x1d661643L), tole(0xd63ac5e6L), tole(0x50aeb748L), tole(0x9bf264edL), 
tole(0x86f75455L), tole(0x4dab87f0L), tole(0xcb3ff55eL), tole(0x006326fbL), 
tole(0xf135942eL), tole(0x3a69478bL), tole(0xbcfd3525L), tole(0x77a1e680L), 
tole(0x6aa4d638L), tole(0xa1f8059dL), tole(0x276c7733L), tole(0xec30a496L), 
tole(0x191c11eeL), tole(0xd240c24bL), tole(0x54d4b0e5L), tole(0x9f886340L), 
tole(0x828d53f8L), tole(0x49d1805dL), tole(0xcf45f2f3L), tole(0x04192156L), 
tole(0xf54f9383L), tole(0x3e134026L), tole(0xb8873288L), tole(0x73dbe12dL), 
tole(0x6eded195L), tole(0xa5820230L), tole(0x2316709eL), tole(0xe84aa33bL), 
tole(0x1aca1375L), tole(0xd196c0d0L), tole(0x5702b27eL), tole(0x9c5e61dbL), 
tole(0x815b5163L), tole(0x4a0782c6L), tole(0xcc93f068L), tole(0x07cf23cdL), 
tole(0xf6999118L), tole(0x3dc542bdL), tole(0xbb513013L), tole(0x700de3b6L), 
tole(0x6d08d30eL), tole(0xa65400abL), tole(0x20c07205L), tole(0xeb9ca1a0L), 
tole(0x11e81eb4L), tole(0xdab4cd11L), tole(0x5c20bfbfL), tole(0x977c6c1aL), 
tole(0x8a795ca2L), tole(0x41258f07L), tole(0xc7b1fda9L), tole(0x0ced2e0cL), 
tole(0xfdbb9cd9L), tole(0x36e74f7cL), tole(0xb0733dd2L), tole(0x7b2fee77L), 
tole(0x662adecfL), tole(0xad760d6aL), tole(0x2be27fc4L), tole(0xe0beac61L), 
tole(0x123e1c2fL), tole(0xd962cf8aL), tole(0x5ff6bd24L), tole(0x94aa6e81L), 
tole(0x89af5e39L), tole(0x42f38d9cL), tole(0xc467ff32L), tole(0x0f3b2c97L), 
tole(0xfe6d9e42L), tole(0x35314de7L), tole(0xb3a53f49L), tole(0x78f9ececL), 
tole(0x65fcdc54L), tole(0xaea00ff1L), tole(0x28347d5fL), tole(0xe368aefaL), 
tole(0x16441b82L), tole(0xdd18c827L), tole(0x5b8cba89L), tole(0x90d0692cL), 
tole(0x8dd55994L), tole(0x46898a31L), tole(0xc01df89fL), tole(0x0b412b3aL), 
tole(0xfa1799efL), tole(0x314b4a4aL), tole(0xb7df38e4L), tole(0x7c83eb41L), 
tole(0x6186dbf9L), tole(0xaada085cL), tole(0x2c4e7af2L), tole(0xe712a957L), 
tole(0x15921919L), tole(0xdececabcL), tole(0x585ab812L), tole(0x93066bb7L), 
tole(0x8e035b0fL), tole(0x455f88aaL), tole(0xc3cbfa04L), tole(0x089729a1L), 
tole(0xf9c19b74L), tole(0x329d48d1L), tole(0xb4093a7fL), tole(0x7f55e9daL), 
tole(0x6250d962L), tole(0xa90c0ac7L), tole(0x2f987869L), tole(0xe4c4abccL)},
{
tole(0x00000000L), tole(0xa6770bb4L), tole(0x979f1129L), tole(0x31e81a9dL), 
tole(0xf44f2413L), tole(0x52382fa7L), tole(0x63d0353aL), tole(0xc5a73e8eL), 
tole(0x33ef4e67L), tole(0x959845d3L), tole(0xa4705f4eL), tole(0x020754faL), 
tole(0xc7a06a74L), tole(0x61d761c0L), tole(0x503f7b5dL), tole(0xf64870e9L), 
tole(0x67de9cceL), tole(0xc1a9977aL), tole(0xf0418de7L), tole(0x56368653L), 
tole(0x9391b8ddL), tole(0x35e6b369L), tole(0x040ea9f4L), tole(0xa279a240L), 
tole(0x5431d2a9L), tole(0xf246d91dL), tole(0xc3aec380L), tole(0x65d9c834L), 
tole(0xa07ef6baL), tole(0x0609fd0eL), tole(0x37e1e793L), tole(0x9196ec27L), 
tole(0xcfbd399cL), tole(0x69ca3228L), tole(0x582228b5L), tole(0xfe552301L), 
tole(0x3bf21d8fL), tole(0x9d85163bL), tole(0xac6d0ca6L), tole(0x0a1a0712L), 
tole(0xfc5277fbL), tole(0x5a257c4fL), tole(0x6bcd66d2L), tole(0xcdba6d66L), 
tole(0x081d53e8L), tole(0xae6a585cL), tole(0x9f8242c1L), tole(0x39f54975L), 
tole(0xa863a552L), tole(0x0e14aee6L), tole(0x3ffcb47bL), tole(0x998bbfcfL), 
tole(0x5c2c8141L), tole(0xfa5b8af5L), tole(0xcbb39068L), tole(0x6dc49bdcL), 
tole(0x9b8ceb35L), tole(0x3dfbe081L), tole(0x0c13fa1cL), tole(0xaa64f1a8L), 
tole(0x6fc3cf26L), tole(0xc9b4c492L), tole(0xf85cde0fL), tole(0x5e2bd5bbL), 
tole(0x440b7579L), tole(0xe27c7ecdL), tole(0xd3946450L), tole(0x75e36fe4L), 
tole(0xb044516aL), tole(0x16335adeL), tole(0x27db4043L), tole(0x81ac4bf7L), 
tole(0x77e43b1eL), tole(0xd19330aaL), tole(0xe07b2a37L), tole(0x460c2183L), 
tole(0x83ab1f0dL), tole(0x25dc14b9L), tole(0x14340e24L), tole(0xb2430590L), 
tole(0x23d5e9b7L), tole(0x85a2e203L), tole(0xb44af89eL), tole(0x123df32aL), 
tole(0xd79acda4L), tole(0x71edc610L), tole(0x4005dc8dL), tole(0xe672d739L), 
tole(0x103aa7d0L), tole(0xb64dac64L), tole(0x87a5b6f9L), tole(0x21d2bd4dL), 
tole(0xe47583c3L), tole(0x42028877L), tole(0x73ea92eaL), tole(0xd59d995eL), 
tole(0x8bb64ce5L), tole(0x2dc14751L), tole(0x1c295dccL), tole(0xba5e5678L), 
tole(0x7ff968f6L), tole(0xd98e6342L), tole(0xe86679dfL), tole(0x4e11726bL), 
tole(0xb8590282L), tole(0x1e2e0936L), tole(0x2fc613abL), tole(0x89b1181fL), 
tole(0x4c162691L), tole(0xea612d25L), tole(0xdb8937b8L), tole(0x7dfe3c0cL), 
tole(0xec68d02bL), tole(0x4a1fdb9fL), tole(0x7bf7c102L), tole(0xdd80cab6L), 
tole(0x1827f438L), tole(0xbe50ff8cL), tole(0x8fb8e511L), tole(0x29cfeea5L), 
tole(0xdf879e4cL), tole(0x79f095f8L), tole(0x48188f65L), tole(0xee6f84d1L), 
tole(0x2bc8ba5fL), tole(0x8dbfb1ebL), tole(0xbc57ab76L), tole(0x1a20a0c2L), 
tole(0x8816eaf2L), tole(0x2e61e146L), tole(0x1f89fbdbL), tole(0xb9fef06fL), 
tole(0x7c59cee1L), tole(0xda2ec555L), tole(0xebc6dfc8L), tole(0x4db1d47cL), 
tole(0xbbf9a495L), tole(0x1d8eaf21L), tole(0x2c66b5bcL), tole(0x8a11be08L), 
tole(0x4fb68086L), tole(0xe9c18b32L), tole(0xd82991afL), tole(0x7e5e9a1bL), 
tole(0xefc8763cL), tole(0x49bf7d88L), tole(0x78576715L), tole(0xde206ca1L), 
tole(0x1b87522fL), tole(0xbdf0599bL), tole(0x8c184306L), tole(0x2a6f48b2L), 
tole(0xdc27385bL), tole(0x7a5033efL), tole(0x4bb82972L), tole(0xedcf22c6L), 
tole(0x28681c48L), tole(0x8e1f17fcL), tole(0xbff70d61L), tole(0x198006d5L), 
tole(0x47abd36eL), tole(0xe1dcd8daL), tole(0xd034c247L), tole(0x7643c9f3L), 
tole(0xb3e4f77dL), tole(0x1593fcc9L), tole(0x247be654L), tole(0x820cede0L), 
tole(0x74449d09L), tole(0xd23396bdL), tole(0xe3db8c20L), tole(0x45ac8794L), 
tole(0x800bb91aL), tole(0x267cb2aeL), tole(0x1794a833L), tole(0xb1e3a387L), 
tole(0x20754fa0L), tole(0x86024414L), tole(0xb7ea5e89L), tole(0x119d553dL), 
tole(0xd43a6bb3L), tole(0x724d6007L), tole(0x43a57a9aL), tole(0xe5d2712eL), 
tole(0x139a01c7L), tole(0xb5ed0a73L), tole(0x840510eeL), tole(0x22721b5aL), 
tole(0xe7d525d4L), tole(0x41a22e60L), tole(0x704a34fdL), tole(0xd63d3f49L), 
tole(0xcc1d9f8bL), tole(0x6a6a943fL), tole(0x5b828ea2L), tole(0xfdf58516L), 
tole(0x3852bb98L), tole(0x9e25b02cL), tole(0xafcdaab1L), tole(0x09baa105L), 
tole(0xfff2d1ecL), tole(0x5985da58L), tole(0x686dc0c5L), tole(0xce1acb71L), 
tole(0x0bbdf5ffL), tole(0xadcafe4bL), tole(0x9c22e4d6L), tole(0x3a55ef62L), 
tole(0xabc30345L), tole(0x0db408f1L), tole(0x3c5c126cL), tole(0x9a2b19d8L), 
tole(0x5f8c2756L), tole(0xf9fb2ce2L), tole(0xc813367fL), tole(0x6e643dcbL), 
tole(0x982c4d22L), tole(0x3e5b4696L), tole(0x0fb35c0bL), tole(0xa9c457bfL), 
tole(0x6c636931L), tole(0xca146285L), tole(0xfbfc7818L), tole(0x5d8b73acL), 
tole(0x03a0a617L), tole(0xa5d7ada3L), tole(0x943fb73eL), tole(0x3248bc8aL), 
tole(0xf7ef8204L), tole(0x519889b0L), tole(0x6070932dL), tole(0xc6079899L), 
tole(0x304fe870L), tole(0x9638e3c4L), tole(0xa7d0f959L), tole(0x01a7f2edL), 
tole(0xc400cc63L), tole(0x6277c7d7L), tole(0x539fdd4aL), tole(0xf5e8d6feL), 
tole(0x647e3ad9L), tole(0xc209316dL), tole(0xf3e12bf0L), tole(0x55962044L), 
tole(0x90311ecaL), tole(0x3646157eL), tole(0x07ae0fe3L), tole(0xa1d90457L), 
tole(0x579174beL), tole(0xf1e67f0aL), tole(0xc00e6597L), tole(0x66796e23L), 
tole(0xa3de50adL), tole(0x05a95b19L), tole(0x34414184L), tole(0x92364a30L)},
{
tole(0x00000000L), tole(0xccaa009eL), tole(0x4225077dL), tole(0x8e8f07e3L), 
tole(0x844a0efaL), tole(0x48e00e64L), tole(0xc66f0987L), tole(0x0ac50919L), 
tole(0xd3e51bb5L), tole(0x1f4f1b2bL), tole(0x91c01cc8L), tole(0x5d6a1c56L), 
tole(0x57af154fL), tole(0x9b0515d1L), tole(0x158a1232L), tole(0xd92012acL), 
tole(0x7cbb312bL), tole(0xb01131b5L), tole(0x3e9e3656L), tole(0xf23436c8L), 
tole(0xf8f13fd1L), tole(0x345b3f4fL), tole(0xbad438acL), tole(0x767e3832L), 
tole(0xaf5e2a9eL), tole(0x63f42a00L), tole(0xed7b2de3L), tole(0x21d12d7dL), 
tole(0x2b142464L), tole(0xe7be24faL), tole(0x69312319L), tole(0xa59b2387L), 
tole(0xf9766256L), tole(0x35dc62c8L), tole(0xbb53652bL), tole(0x77f965b5L), 
tole(0x7d3c6cacL), tole(0xb1966c32L), tole(0x3f196bd1L), tole(0xf3b36b4fL), 
tole(0x2a9379e3L), tole(0xe639797dL), tole(0x68b67e9eL), tole(0xa41c7e00L), 
tole(0xaed97719L), tole(0x62737787L), tole(0xecfc7064L), tole(0x205670faL), 
tole(0x85cd537dL), tole(0x496753e3L), tole(0xc7e85400L), tole(0x0b42549eL), 
tole(0x01875d87L), tole(0xcd2d5d19L), tole(0x43a25afaL), tole(0x8f085a64L), 
tole(0x562848c8L), tole(0x9a824856L), tole(0x140d4fb5L), tole(0xd8a74f2bL), 
tole(0xd2624632L), tole(0x1ec846acL), tole(0x9047414fL), tole(0x5ced41d1L), 
tole(0x299dc2edL), tole(0xe537c273L), tole(0x6bb8c590L), tole(0xa712c50eL), 
tole(0xadd7cc17L), tole(0x617dcc89L), tole(0xeff2cb6aL), tole(0x2358cbf4L), 
tole(0xfa78d958L), tole(0x36d2d9c6L), tole(0xb85dde25L), tole(0x74f7debbL), 
tole(0x7e32d7a2L), tole(0xb298d73cL), tole(0x3c17d0dfL), tole(0xf0bdd041L), 
tole(0x5526f3c6L), tole(0x998cf358L), tole(0x1703f4bbL), tole(0xdba9f425L), 
tole(0xd16cfd3cL), tole(0x1dc6fda2L), tole(0x9349fa41L), tole(0x5fe3fadfL), 
tole(0x86c3e873L), tole(0x4a69e8edL), tole(0xc4e6ef0eL), tole(0x084cef90L), 
tole(0x0289e689L), tole(0xce23e617L), tole(0x40ace1f4L), tole(0x8c06e16aL), 
tole(0xd0eba0bbL), tole(0x1c41a025L), tole(0x92cea7c6L), tole(0x5e64a758L), 
tole(0x54a1ae41L), tole(0x980baedfL), tole(0x1684a93cL), tole(0xda2ea9a2L), 
tole(0x030ebb0eL), tole(0xcfa4bb90L), tole(0x412bbc73L), tole(0x8d81bcedL), 
tole(0x8744b5f4L), tole(0x4beeb56aL), tole(0xc561b289L), tole(0x09cbb217L), 
tole(0xac509190L), tole(0x60fa910eL), tole(0xee7596edL), tole(0x22df9673L), 
tole(0x281a9f6aL), tole(0xe4b09ff4L), tole(0x6a3f9817L), tole(0xa6959889L), 
tole(0x7fb58a25L), tole(0xb31f8abbL), tole(0x3d908d58L), tole(0xf13a8dc6L), 
tole(0xfbff84dfL), tole(0x37558441L), tole(0xb9da83a2L), tole(0x7570833cL), 
tole(0x533b85daL), tole(0x9f918544L), tole(0x111e82a7L), tole(0xddb48239L), 
tole(0xd7718b20L), tole(0x1bdb8bbeL), tole(0x95548c5dL), tole(0x59fe8cc3L), 
tole(0x80de9e6fL), tole(0x4c749ef1L), tole(0xc2fb9912L), tole(0x0e51998cL), 
tole(0x04949095L), tole(0xc83e900bL), tole(0x46b197e8L), tole(0x8a1b9776L), 
tole(0x2f80b4f1L), tole(0xe32ab46fL), tole(0x6da5b38cL), tole(0xa10fb312L), 
tole(0xabcaba0bL), tole(0x6760ba95L), tole(0xe9efbd76L), tole(0x2545bde8L), 
tole(0xfc65af44L), tole(0x30cfafdaL), tole(0xbe40a839L), tole(0x72eaa8a7L), 
tole(0x782fa1beL), tole(0xb485a120L), tole(0x3a0aa6c3L), tole(0xf6a0a65dL), 
tole(0xaa4de78cL), tole(0x66e7e712L), tole(0xe868e0f1L), tole(0x24c2e06fL), 
tole(0x2e07e976L), tole(0xe2ade9e8L), tole(0x6c22ee0bL), tole(0xa088ee95L), 
tole(0x79a8fc39L), tole(0xb502fca7L), tole(0x3b8dfb44L), tole(0xf727fbdaL), 
tole(0xfde2f2c3L), tole(0x3148f25dL), tole(0xbfc7f5beL), tole(0x736df520L), 
tole(0xd6f6d6a7L), tole(0x1a5cd639L), tole(0x94d3d1daL), tole(0x5879d144L), 
tole(0x52bcd85dL), tole(0x9e16d8c3L), tole(0x1099df20L), tole(0xdc33dfbeL), 
tole(0x0513cd12L), tole(0xc9b9cd8cL), tole(0x4736ca6fL), tole(0x8b9ccaf1L), 
tole(0x8159c3e8L), tole(0x4df3c376L), tole(0xc37cc495L), tole(0x0fd6c40bL), 
tole(0x7aa64737L), tole(0xb60c47a9L), tole(0x3883404aL), tole(0xf42940d4L), 
tole(0xfeec49cdL), tole(0x32464953L), tole(0xbcc94eb0L), tole(0x70634e2eL), 
tole(0xa9435c82L), tole(0x65e95c1cL), tole(0xeb665bffL), tole(0x27cc5b61L), 
tole(0x2d095278L), tole(0xe1a352e6L), tole(0x6f2c5505L), tole(0xa386559bL), 
tole(0x061d761cL), tole(0xcab77682L), tole(0x44387161L), tole(0x889271ffL), 
tole(0x825778e6L), tole(0x4efd7878L), tole(0xc0727f9bL), tole(0x0cd87f05L), 
tole(0xd5f86da9L), tole(0x19526d37L), tole(0x97dd6ad4L), tole(0x5b776a4aL), 
tole(0x51b26353L), tole(0x9d1863cdL), tole(0x1397642eL), tole(0xdf3d64b0L), 
tole(0x83d02561L), tole(0x4f7a25ffL), tole(0xc1f5221cL), tole(0x0d5f2282L), 
tole(0x079a2b9bL), tole(0xcb302b05L), tole(0x45bf2ce6L), tole(0x89152c78L), 
tole(0x50353ed4L), tole(0x9c9f3e4aL), tole(0x121039a9L), tole(0xdeba3937L), 
tole(0xd47f302eL), tole(0x18d530b0L), tole(0x965a3753L), tole(0x5af037cdL), 
tole(0xff6b144aL), tole(0x33c114d4L), tole(0xbd4e1337L), tole(0x71e413a9L), 
tole(0x7b211ab0L), tole(0xb78b1a2eL), tole(0x39041dcdL), tole(0xf5ae1d53L), 
tole(0x2c8e0fffL), tole(0xe0240f61L), tole(0x6eab0882L), tole(0xa201081cL), 
tole(0xa8c40105L), tole(0x646e019bL), tole(0xeae10678L), tole(0x264b06e6L)},
};

static inline u32 __pure
crc32_body(u32 crc, unsigned char const *buf, size_t len, const u32 (*tab)[256])
{
# ifdef __LITTLE_ENDIAN
#  define DO_CRC(x) crc = t0[(crc ^ (x)) & 255] ^ (crc >> 8)
#  define DO_CRC4 (t3[(q) & 255] ^ t2[(q >> 8) & 255] ^ \
		   t1[(q >> 16) & 255] ^ t0[(q >> 24) & 255])
#  define DO_CRC8 (t7[(q) & 255] ^ t6[(q >> 8) & 255] ^ \
		   t5[(q >> 16) & 255] ^ t4[(q >> 24) & 255])
# else
#  define DO_CRC(x) crc = t0[((crc >> 24) ^ (x)) & 255] ^ (crc << 8)
#  define DO_CRC4 (t0[(q) & 255] ^ t1[(q >> 8) & 255] ^ \
		   t2[(q >> 16) & 255] ^ t3[(q >> 24) & 255])
#  define DO_CRC8 (t4[(q) & 255] ^ t5[(q >> 8) & 255] ^ \
		   t6[(q >> 16) & 255] ^ t7[(q >> 24) & 255])
# endif
	const u32 *b;
	size_t    rem_len;
# ifdef CONFIG_X86
	size_t i;
# endif
	const u32 *t0=tab[0], *t1=tab[1], *t2=tab[2], *t3=tab[3];
# if CRC_LE_BITS != 32
	const u32 *t4 = tab[4], *t5 = tab[5], *t6 = tab[6], *t7 = tab[7];
# endif
	u32 q;

	/* Align it */
	if (unlikely((long)buf & 3 && len)) {
		do {
			DO_CRC(*buf++);
		} while ((--len) && ((long)buf)&3);
	}

# if CRC_LE_BITS == 32
	rem_len = len & 3;
	len = len >> 2;
# else
	rem_len = len & 7;
	len = len >> 3;
# endif

	b = (const u32 *)buf;
# ifdef CONFIG_X86
	--b;
	for (i = 0; i < len; i++) {
# else
	for (--b; len; --len) {
# endif
		q = crc ^ *++b; /* use pre increment for speed */
# if CRC_LE_BITS == 32
		crc = DO_CRC4;
# else
		crc = DO_CRC8;
		q = *++b;
		crc ^= DO_CRC4;
# endif
	}
	len = rem_len;
	/* And the last few bytes */
	if (len) {
		u8 *p = (u8 *)(b + 1) - 1;
# ifdef CONFIG_X86
		for (i = 0; i < len; i++)
			DO_CRC(*++p); /* use pre increment for speed */
# else
		do {
			DO_CRC(*++p); /* use pre increment for speed */
		} while (--len);
# endif
	}
	return crc;
#undef DO_CRC
#undef DO_CRC4
#undef DO_CRC8
}

static inline u32 __pure crc32_le_generic(u32 crc, unsigned char const *p,
					  size_t len, const u32 (*tab)[256],
					  u32 polynomial)
{
#if CRC_LE_BITS == 1
	int i;
	while (len--) {
		crc ^= *p++;
		for (i = 0; i < 8; i++)
			crc = (crc >> 1) ^ ((crc & 1) ? polynomial : 0);
	}
# elif CRC_LE_BITS == 2
	while (len--) {
		crc ^= *p++;
		crc = (crc >> 2) ^ tab[0][crc & 3];
		crc = (crc >> 2) ^ tab[0][crc & 3];
		crc = (crc >> 2) ^ tab[0][crc & 3];
		crc = (crc >> 2) ^ tab[0][crc & 3];
	}
# elif CRC_LE_BITS == 4
	while (len--) {
		crc ^= *p++;
		crc = (crc >> 4) ^ tab[0][crc & 15];
		crc = (crc >> 4) ^ tab[0][crc & 15];
	}
# elif CRC_LE_BITS == 8
	/* aka Sarwate algorithm */
	while (len--) {
		crc ^= *p++;
		crc = (crc >> 8) ^ tab[0][crc & 255];
	}
# else
	crc = (__force u32) __cpu_to_le32(crc);
	crc = crc32_body(crc, p, len, tab);
	crc = __le32_to_cpu((__force __le32)crc);
#endif
	return crc;
}

static u32 __pure crc32_le(u32 crc, unsigned char const *p, size_t len)
{
	return crc32_le_generic(crc, p, len, crc32table_le, CRC32_POLY_LE);
}

#if 0
EXPORT_SYMBOL(crc32_le);
#endif

#define crc32(seed, data, length)  crc32_le(seed, (unsigned char const *)(data), length)
