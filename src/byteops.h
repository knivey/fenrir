#if !defined(BYTEOPS_H)
#define BYTEOPS_H

#include <stdint.h>

#include "compiler.h"

#if defined(__LITTLE_ENDIAN__)
#  define HOST_LITTLE_ENDIAN	1
#  define HOST_BIG_ENDIAN	0
#elif defined(__BIG_ENDIAN__)
#  define HOST_LITTLE_ENDIAN	0
#  define HOST_BIG_ENDIAN	1
#elif defined(__BYTE_ORDER__)
#  if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define HOST_LITTLE_ENDIAN	1
#    define HOST_BIG_ENDIAN	0
#  elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define HOST_LITTLE_ENDIAN	0
#    define HOST_BIG_ENDIAN	1
#  endif
#endif /* defined(__LITTLE_ENDIAN__) */

#if defined(HOST_LITTLE_ENDIAN)
#define host_is_little_endian()	HOST_LITTLE_ENDIAN
#define host_is_big_endian()	HOST_BIG_ENDIAN
#else
static force_inline int host_is_little_endian(void)
{
	const union {
		uint32_t u32;
		uint8_t u8[4];
	} x = { .u32 = 1 };
	return x.u8[0];
}

static force_inline int host_is_big_endian(void)
{
	return !host_is_little_endian();
}
#endif /* defined(HOST_LITTLE_ENDIAN) */

#if __has_builtin(__builtin_bswap16)
static force_inline uint16_t bswap16(uint16_t x)
{
	return __builtin_bswap16(x);
}
#else
static force_inline uint16_t bswap16(uint16_t x)
{
	return (((x & 0xff00) >> 8) |
		((x & 0x00ff) << 8));
}
#endif /* __has_builtin(__builtin_bswap16) */

#if __has_builtin(__builtin_bswap32)
static force_inline uint32_t bswap32(uint32_t x)
{
	return __builtin_bswap32(x);
}
#else
static force_inline uint32_t bswap32(uint32_t x)
{
	return (((x & 0xff000000u) >> 24) |
		((x & 0x00ff0000u) >>  8) |
		((x & 0x0000ff00u) <<  8) |
		((x & 0x000000ffu) << 24));
}
#endif /* __has_builtin(__builtin_bswap32) */

#if __has_builtin(__builtin_bswap64)
static force_inline uint64_t bswap64(uint64_t x)
{
	return __builtin_bswap64(x);
}
#else
static force_inline uint64_t bswap64(uint64_t x)
{
	return (((x & 0xff00000000000000ul) >> 56) |
		((x & 0x00ff000000000000ul) >> 40) |
		((x & 0x0000ff0000000000ul) >> 24) |
		((x & 0x000000ff00000000ul) >>  8) |
		((x & 0x00000000ff000000ul) <<  8) |
		((x & 0x0000000000ff0000ul) << 24) |
		((x & 0x000000000000ff00ul) << 40) |
		((x & 0x00000000000000fful) << 56));
}
#endif /* __has_builtin(__builtin_bswap64) */

static force_inline uint16_t host_to_le16(uint16_t x)
{
	return host_is_little_endian() ? x : bswap16(x);
}

static force_inline uint16_t le16_to_host(uint16_t x)
{
	return host_to_le16(x);
}

static force_inline uint32_t host_to_le32(uint32_t x)
{
	return host_is_little_endian() ? x : bswap32(x);
}

static force_inline uint32_t le32_to_host(uint32_t x)
{
	return host_to_le32(x);
}

static force_inline uint64_t host_to_le64(uint64_t x)
{
	return host_is_little_endian() ? x : bswap64(x);
}

static force_inline uint64_t le64_to_host(uint64_t x)
{
	return host_to_le64(x);
}

static force_inline uint16_t host_to_be16(uint16_t x)
{
	return host_is_big_endian() ? x : bswap16(x);
}

static force_inline uint16_t be16_to_host(uint16_t x)
{
	return host_to_be16(x);
}

static force_inline uint32_t host_to_be32(uint32_t x)
{
	return host_is_big_endian() ? x : bswap32(x);
}

static force_inline uint32_t be32_to_host(uint32_t x)
{
	return host_to_be32(x);
}

static force_inline uint64_t host_to_be64(uint64_t x)
{
	return host_is_big_endian() ? x : bswap64(x);
}

static force_inline uint64_t be64_to_host(uint64_t x)
{
	return host_to_be64(x);
}

#endif /* !defined(BYTEOPS_H) */
