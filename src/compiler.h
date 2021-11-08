#if !defined(COMPILER_H)
#define COMPILER_H

#if !defined(__has_builtin)
#define __has_builtin(x)	0
#endif

#if !defined(__has_attribute)
#define __has_attribute(x)	0
#define __attribute__(x)
#endif

#if __has_builtin(__builtin_expect)
#define likely(x)		__builtin_expect(!!(x), 1)
#define unlikely(x)		__builtin_expect(!!(x), 0)
#else
#define likely(x)
#define unlikely(x)
#endif

#if __has_attribute(__noinline__)
#define never_inline		__attribute__((__noinline__))
#else
#define never_inline
#endif

#if __has_attribute(__always_inline__)
#define force_inline		__attribute__((__always_inline__)) inline
#else
#define force_inline		inline
#endif

#if __has_attribute(__unused__)
#define maybe_unused		__attribute__((__unused__))
#define always_unused		__attribute__((__unused__))
#else
#define maybe_unused
#define always_unused
#endif

#if __has_attribute(__format__)
#define format(type, fmt, args)	__attribute__((__format__(type, fmt, args)))
#else
#define format(type, fmt, args)
#endif

#define format_printf(fmt)	format(__printf__, fmt, fmt + 1)
#define format_vprintf(fmt)	format(__printf__, fmt, 0)
#define format_scanf(fmt)	format(__scanf__, fmt, fmt + 1)
#define format_vscanf(fmt)	format(__scanf__, fmt, 0)
#define format_strftime(fmt)	format(__strftime__, fmt, 0)

#endif /* !defined(COMPILER_H) */
