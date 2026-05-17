#ifndef STRING_SSO_H
#define STRING_SSO_H

#include <stddef.h>

#define SSO 15

typedef struct String String;

/* lifecycle */
String *string_create(void);
void string_destroy(String *s);

/* info */
size_t string_size(const String *s);
const char *string_c_str(const String *s);

/* core */
void string_clear(String *s);
int string_push_back(String *s, char c);
int string_reserve(String *s, size_t new_cap);

/* utilities */
void string_read(String *s);
String *string_clone(const String *s);
int string_compare(const String *a, const String *b);

/* optional helper for generic containers */
int string_cmp_qsort(const void *a, const void *b);

#endif