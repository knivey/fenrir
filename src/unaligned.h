#if !defined(UNALIGNED_H)
#define UNALIGNED_H

#include <stdint.h>
#include <string.h>

#include "byteops.h"

static force_inline uint16_t get_unaligned_u16(const void *p)
{
	uint16_t val;

	memcpy(&val, p, sizeof(val));
	return val;
}

static force_inline uint32_t get_unaligned_u32(const void *p)
{
	uint32_t val;

	memcpy(&val, p, sizeof(val));
	return val;
}

static force_inline uint64_t get_unaligned_u64(const void *p)
{
	uint64_t val;

	memcpy(&val, p, sizeof(val));
	return val;
}

static force_inline void put_unaligned_u16(void *p, uint16_t val)
{
	memcpy(p, &val, sizeof(val));
}

static force_inline void put_unaligned_u32(void *p, uint32_t val)
{
	memcpy(p, &val, sizeof(val));
}

static force_inline void put_unaligned_u64(void *p, uint64_t val)
{
	memcpy(p, &val, sizeof(val));
}

static inline uint16_t get_unaligned_le16(const void *p)
{
	return host_to_le16(get_unaligned_u16(p));
}

static inline uint32_t get_unaligned_le32(const void *p)
{
	return host_to_le32(get_unaligned_u32(p));
}

static inline uint64_t get_unaligned_le64(const void *p)
{
	return host_to_le64(get_unaligned_u64(p));
}

static inline uint16_t get_unaligned_be16(const void *p)
{
	return host_to_be16(get_unaligned_u16(p));
}

static inline uint32_t get_unaligned_be32(const void *p)
{
	return host_to_be32(get_unaligned_u32(p));
}

static inline uint64_t get_unaligned_be64(const void *p)
{
	return host_to_be64(get_unaligned_u64(p));
}

static inline void put_unaligned_le16(void *p, uint16_t val)
{
	put_unaligned_u16(p, host_to_le16(val));
}

static inline void put_unaligned_le32(void *p, uint32_t val)
{
	put_unaligned_u32(p, host_to_le32(val));
}

static inline void put_unaligned_le64(void *p, uint64_t val)
{
	put_unaligned_u64(p, host_to_le64(val));
}

static inline void put_unaligned_be16(void *p, uint16_t val)
{
	put_unaligned_u16(p, host_to_be16(val));
}

static inline void put_unaligned_be32(void *p, uint32_t val)
{
	put_unaligned_u32(p, host_to_be32(val));
}

static inline void put_unaligned_be64(void *p, uint64_t val)
{
	put_unaligned_u64(p, host_to_be64(val));
}

#endif /* !defined(UNALIGNED_H) */
