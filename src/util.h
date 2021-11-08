#if !defined(UTIL_H)
#define UTIL_H

#include <stdbool.h>
#include <stddef.h>

#include "compiler.h"
#include "bitops.h"

#define ARRAY_LEN(x)	(sizeof(x) / sizeof((x)[0]))

#define container_of(ptr, type, field) \
	((type *)((char *)(ptr) - offsetof(type, field)))

#if __has_builtin(__builtin_popcountl)
static force_inline bool is_power_of_two(unsigned long x)
{
	return __builtin_popcountl(x) == 1;
}
#else
static force_inline bool is_power_of_two(unsigned long x)
{
	return !(x & (x - 1)) && x;
}
#endif /* __has_builtin(__builtin_popcountl) */

static force_inline unsigned long round_up_power_of_two(unsigned long x)
{
	return (x < 2) ? 1ul : 1ul << flsb(x - 1);
}

#endif /* !defined(UTIL_H) */
