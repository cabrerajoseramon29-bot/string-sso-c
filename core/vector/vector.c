#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "vector.h"

struct Vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t elem_size;
};

/* ================= LIFECYCLE ================= */

Vector *vector_create(size_t elem_size, size_t initial_capacity) {
    if (elem_size == 0) return NULL;

    Vector *v = malloc(sizeof(Vector));
    if (!v) return NULL;

    v->elem_size = elem_size;
    v->size = 0;
    v->capacity = (initial_capacity > 0) ? initial_capacity : 4;

    v->data = malloc(v->capacity * elem_size);
    if (!v->data) {
        free(v);
        return NULL;
    }

    return v;
}

void vector_destroy(Vector *v) {
    if (!v) return;
    free(v->data);
    free(v);
}

/* ================= INFO ================= */

size_t vector_size(const Vector *v) {
    return v ? v->size : 0;
}

size_t vector_capacity(const Vector *v) {
    return v ? v->capacity : 0;
}

/* ================= ACCESS ================= */

void *vector_get(const Vector *v, size_t index) {
    if (!v || index >= v->size) return NULL;
    return (char *)v->data + index * v->elem_size;
}

/* ================= RESIZE CORE ================= */

int vector_reserve(Vector *v, size_t new_capacity) {
    if (!v) return -1;
    if (new_capacity <= v->capacity) return 0;

    void *new_data = realloc(v->data, new_capacity * v->elem_size);
    if (!new_data) return -1;

    v->data = new_data;
    v->capacity = new_capacity;

    return 0;
}

void vector_clear(Vector *v) {
    if (!v) return;
    v->size = 0;
}

int vector_shrink_to_fit(Vector *v) {
    if (!v) return -1;

    if (v->size == v->capacity) return 0;

    if (v->size == 0) {
        free(v->data);
        v->data = NULL;
        v->capacity = 0;
        return 0;
    }

    void *new_data = realloc(v->data, v->size * v->elem_size);
    if (!new_data) return -1;

    v->data = new_data;
    v->capacity = v->size;

    return 0;
}

/* ================= INTERNAL HELP ================= */

static int ensure_capacity(Vector *v, size_t min_cap) {
    if (v->capacity >= min_cap) return 0;

    size_t new_cap = v->capacity ? v->capacity : 4;

    while (new_cap < min_cap) {
        if (new_cap > SIZE_MAX / 2) return -1;
        new_cap *= 2;
    }

    return vector_reserve(v, new_cap);
}

/* ================= OPERATIONS ================= */

int vector_push(Vector *v, const void *elem) {
    if (!v || !elem) return -1;

    if (ensure_capacity(v, v->size + 1) != 0)
        return -1;

    void *dest = (char *)v->data + v->size * v->elem_size;
    memcpy(dest, elem, v->elem_size);

    v->size++;
    return 0;
}

int vector_pop(Vector *v, void *out) {
    if (!v || v->size == 0) return -1;

    void *src = (char *)v->data + (v->size - 1) * v->elem_size;

    if (out)
        memcpy(out, src, v->elem_size);

    v->size--;
    return 0;
}

int vector_set(Vector *v, size_t index, const void *elem){
    if(!v || !elem || index >= v->size)return -1;

    void *dest = (char *)v->data + index * v->elem_size;
    memcpy(dest, elem, v->elem_size);
    return 0;
}

int vector_remove_at(Vector *v, size_t index, void *out) {
    if (!v || index >= v->size) return -1;

    void *target = (char *)v->data + index * v->elem_size;

    if (out)
        memcpy(out, target, v->elem_size);

    size_t elements_after = v->size - index - 1;

    if (elements_after > 0) {
        void *next = (char *)target + v->elem_size;
        memmove(target, next, elements_after * v->elem_size);
    }

    v->size--;
    return 0;
}

/* ================= SORT ================= */

void vector_sort(Vector *v, int (*cmp)(const void *, const void *)) {
    if (!v || !cmp) return;
    qsort(v->data, v->size, v->elem_size, cmp);
}