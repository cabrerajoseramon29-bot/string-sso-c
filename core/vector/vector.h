#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct Vector Vector;

/* lifecycle */
Vector *vector_create(size_t elem_size, size_t initial_capacity);
void vector_destroy(Vector *v);

/* info */
size_t vector_size(const Vector *v);
size_t vector_capacity(const Vector *v);

/* access */
void *vector_get(const Vector *v, size_t index);

/* memory control */
int vector_reserve(Vector *v, size_t new_capacity);
void vector_clear(Vector *v);
int vector_shrink_to_fit(Vector *v);

/* operations */
int vector_push(Vector *v, const void *elem);
int vector_pop(Vector *v, void *out);
int vector_set(Vector *v, size_t index, const void *elem);
int vector_remove_at(Vector *v, size_t index, void *out);

/* sorting (GENERIC) */
void vector_sort(Vector *v, int (*cmp)(const void *, const void *));

#endif