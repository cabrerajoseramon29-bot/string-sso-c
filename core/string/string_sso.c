#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "string_sso.h"

struct String {
    char sso[SSO + 1];
    char *data;
    size_t size;
    size_t cap;
};

/* ================= LIFECYCLE ================= */

String *string_create(void) {
    String *s = malloc(sizeof(String));
    if (!s) return NULL;

    s->data = s->sso;
    s->size = 0;
    s->cap = SSO;
    s->sso[0] = '\0';

    return s;
}

void string_destroy(String *s) {
    if (!s) return;

    if (s->data != s->sso)
        free(s->data);

    free(s);
}

/* ================= INFO ================= */

size_t string_size(const String *s) {
    return s ? s->size : 0;
}

const char *string_c_str(const String *s) {
    return s ? s->data : NULL;
}

/* ================= CORE ================= */

void string_clear(String *s) {
    if (!s) return;

    s->size = 0;
    s->data[0] = '\0';
}

int string_reserve(String *s, size_t new_cap) {
    if (!s || new_cap <= s->cap) return 0;

    char *new_data = malloc(new_cap + 1);
    if (!new_data) return -1;

    memcpy(new_data, s->data, s->size);
    new_data[s->size] = '\0';

    if (s->data != s->sso)
        free(s->data);

    s->data = new_data;
    s->cap = new_cap;

    return 0;
}

int string_push_back(String *s, char c) {
    if (!s) return -1;

    if (s->size + 1 > s->cap) {
        size_t new_cap = s->cap * 2;
        if (string_reserve(s, new_cap) != 0)
            return -1;
    }

    s->data[s->size++] = c;
    s->data[s->size] = '\0';

    return 0;
}

/* ================= READ ================= */
void string_read(String *s){
#if defined(_POSIX_C_SOURCE) || defined (_GNU_SOURCE)
    char *line = NULL;
    size_t len = 0;
    ssize_t n = getline(&line, &len, stdin);

    if (n > 0) {
        if(line[n-1] == '\n'){
            line[n-1] = '\0';
            n--;
        }

        string_clear(s);
        if (string_reserve(s, (size_t)n) != 0) {
            free(line);
            return;
        }
        memcpy(s->data, line, (size_t)n);
        s->size = (size_t)n;
        s->data[s->size] = '\0';
    }
    free(line);
#else
    char buffer[4096];

    if(fgets(buffer, sizeof(buffer), stdin)){
        string_clear(s);

        for (size_t i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
            string_push_back(s, buffer[i]);
        }
    }
#endif
}


/* ================= COPY ================= */

String *string_clone(const String *src) {
    if (!src) return NULL;

    String *s = string_create();
    if (!s) return NULL;

    if (string_reserve(s, src->size) != 0) {
        string_destroy(s);
        return NULL;
    }

    memcpy(s->data, src->data, src->size);
    s->size = src->size;
    s->data[s->size] = '\0';

    return s;
}

/* ================= COMPARE ================= */

int string_compare(const String *a, const String *b) {
    if (!a || !b) return 0;

    size_t i = 0;

    while (i < a->size && i < b->size) {
        char c1 = tolower((unsigned char)a->data[i]);
        char c2 = tolower((unsigned char)b->data[i]);

        if (c1 != c2)
            return c1 - c2;

        i++;
    }

    if (a->size == b->size) return 0;
    return (a->size < b->size) ? -1 : 1;
}

/* ================= QSORT ADAPTER ================= */

int string_cmp_qsort(const void *a, const void *b) {
    const String *sa = *(const String **)a;
    const String *sb = *(const String **)b;

    return string_compare(sa, sb);
}