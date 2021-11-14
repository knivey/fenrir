#if !defined(STRINGLIB_H)
#define STRINGLIB_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "compiler.h"

int vscnprintf(char *restrict s, size_t n, const char *restrict format,
	       va_list args) format_vprintf(3);

int scnprintf(char *restrict s, size_t n, const char *restrict format,
	      ...) format_printf(3);

bool sglob(const char *mask, const char *text);
bool scaseglob(const char *mask, const char *text);
int scasecmp(const char *s1, const char *s2);
int sncasecmp(const char *s1, const char *s2, size_t n);
size_t snlen(const char *s, size_t n);
void *mdup(const void *p, size_t n);
char *sdup(const char *s);
char *sndup(const char *s, size_t n);
size_t sncpy(char *restrict dest, const char *restrict src, size_t n);
size_t szcpy(char *restrict dest, const char *restrict src, size_t n);
char *ssep(char **restrict str_ptr, const char *restrict delim);
char *stok(char **restrict str_ptr, const char *restrict delim);
size_t svsplit(char *dest[], char *src, size_t dest_size);
size_t svircsplit(char *dest[], char *src, size_t dest_size);
size_t svunsplit(char *dest, size_t dest_size, char *src[], size_t src_size);

#endif /* !defined(STRINGLIB_H) */
