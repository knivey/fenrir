#if !defined(BITOPS_H)
#define BITOPS_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "compiler.h"

static force_inline uint8_t rol8(uint8_t x, size_t offset)
{
	return (x << (offset & 7)) | (x >> (-offset & 7));
}

static force_inline uint16_t rol16(uint16_t x, size_t offset)
{
	return (x << (offset & 15)) | (x >> (-offset & 15));
}

static force_inline uint32_t rol32(uint32_t x, size_t offset)
{
	return (x << (offset & 31)) | (x >> (-offset & 31));
}

static force_inline uint64_t rol64(uint64_t x, size_t offset)
{
	return (x << (offset & 63)) | (x >> (-offset & 63));
}

static force_inline uint8_t ror8(uint8_t x, size_t offset)
{
	return (x >> (offset & 7)) | (x << (-offset & 7));
}

static force_inline uint16_t ror16(uint16_t x, size_t offset)
{
	return (x >> (offset & 15)) | (x << (-offset & 15));
}

static force_inline uint32_t ror32(uint32_t x, size_t offset)
{
	return (x >> (offset & 31)) | (x << (-offset & 31));
}

static force_inline uint64_t ror64(uint64_t x, size_t offset)
{
	return (x >> (offset & 63)) | (x << (-offset & 63));
}

#if __has_builtin(__builtin_clzl)
static force_inline int flsb(unsigned long x)
{
	return (CHAR_BIT * sizeof(x)) - __builtin_clzl(x);
}
#else
static force_inline int flsb(unsigned long x)
{
	size_t ret = CHAR_BIT * sizeof(x);
	unsigned long mask = ~0ul;

	for (size_t ii = (ret >> 1); ii; ii >>= 1) {
		mask <<= ii;
		if (!(x & mask)) {
			x <<= ii;
			ret -= ii;
		}
	}
	return ret;
}
#endif /* __has_builtin(__builtin_clzl) */

#if __has_builtin(__builtin_ffsl)
static force_inline int ffsb(unsigned long x)
{
	return __builtin_ffsl(x);
}
#else
static force_inline int ffsb(unsigned long x)
{
	size_t ret = 1;
	unsigned long mask = ~0ul;
	const size_t bits = CHAR_BIT * sizeof(x);

	for (size_t ii = (bits >> 1); ii; ii >>= 1) {
		mask >>= ii;
		if (!(x & mask)) {
			x >>= ii;
			ret += ii;
		}
	}
	return ret;
}
#endif /* __has_builtin(__builtin_ffsl) */

#endif /* !defined(BITOPS_H) */
