#if !defined(MINMAX_H)
#define MINMAX_H

#define minmax_gen(prefix, x, y) _Generic((x) + (y),	\
	int: prefix ## _int,				\
	long: prefix ## _long,				\
	unsigned int: prefix ## _uint,			\
	unsigned long: prefix ## _ulong,		\
	float: prefix ## _float,			\
	double: prefix ## _double,			\
	long double: prefix ## _ldouble			\
)((x), (y))

#define min(x, y)		minmax_gen(min, (x), (y))
#define max(x, y)		minmax_gen(max, (x), (y))

#define min3(x, y, z)		min(min((x), (y)), (z))
#define max3(x, y, z)		max(max((x), (y)), (z))

#define min_unsafe(x, y)	(((x) < (y)) ? (x) : (y))
#define max_unsafe(x, y)	(((x) > (y)) ? (x) : (y))

static inline int min_int(int x, int y)
{
	return min_unsafe(x, y);
}

static inline int max_int(int x, int y)
{
	return max_unsafe(x, y);
}

static inline long min_long(long x, long y)
{
	return min_unsafe(x, y);
}

static inline long max_long(long x, long y)
{
	return max_unsafe(x, y);
}

static inline unsigned int min_uint(unsigned int x, unsigned int y)
{
	return min_unsafe(x, y);
}

static inline unsigned int max_uint(unsigned int x, unsigned int y)
{
	return max_unsafe(x, y);
}

static inline unsigned long min_ulong(unsigned long x, unsigned long y)
{
	return min_unsafe(x, y);
}

static inline unsigned long max_ulong(unsigned long x, unsigned long y)
{
	return max_unsafe(x, y);
}

static inline float min_float(float x, float y)
{
	return min_unsafe(x, y);
}

static inline float max_float(float x, float y)
{
	return max_unsafe(x, y);
}

static inline double min_double(double x, double y)
{
	return min_unsafe(x, y);
}

static inline double max_double(double x, double y)
{
	return max_unsafe(x, y);
}

static inline long double min_ldouble(long double x, long double y)
{
	return min_unsafe(x, y);
}

static inline long double max_ldouble(long double x, long double y)
{
	return max_unsafe(x, y);
}

#undef min_unsafe
#undef max_unsafe

#endif /* !defined(MINMAX_H) */
