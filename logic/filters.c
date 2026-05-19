#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "../core/vector/vector.h"
#include "../core/string/string_sso.h"
#include "filters.h"

static int string_start(String *s,const String *prefix){
    if(!s || !prefix)return 0;

    size_t pref_len = string_size(prefix);
    if(pref_len > string_size(s))return 0;

    for (size_t i = 0; i < pref_len; i++) {
        char c1 = tolower((unsigned char)string_c_str(prefix)[i]);
        char c2 = tolower((unsigned char)string_c_str(s)[i]);

        if(c1 != c2)return 0;
    }
    return 1;
}

Vector *filter_by_length(Vector *v){
    if(!v)return NULL;
    Vector *filtered = vector_create(sizeof(String *), 0);
    if(!filtered){
        vector_destroy(filtered);
        return NULL;
    }
    size_t n = vector_size(v);
    size_t max = 0;

    for (size_t i = 0; i < n; i++) {
        String **ptr = vector_get(v, i);
        String *s = *ptr;
        size_t len_str = string_size(s);

        if (len_str > max) {
            vector_clear(filtered);  //Works provided that the filtered data contains only references and does not own the strings.
            max = len_str;
            vector_push(filtered, &s);
        }else if (len_str == max) {
            vector_push(filtered, &s);
        }
    }
    return filtered;
}

Vector *filter_by_exact_length(Vector *v, size_t len){
    if(!v || len == 0)return NULL;
    Vector *filtered = vector_create(sizeof(String *), 0);
    if(!filtered)return NULL;
    size_t n = vector_size(v);

    for (size_t i = 0; i < n; i++) {
        String **ptr = vector_get(v, i);
        String *s = *ptr;

        if (len == string_size(s)) {
            vector_push(filtered, &s);
        }   
    }
    return filtered;
}

Vector *filter_by_prefix(Vector *v, const String *prefix){
    if(!v || !prefix)return NULL;
    Vector *filtered = vector_create(sizeof(String *), 0);
    if(!filtered)return NULL;
    size_t n = vector_size(v);

    for (size_t i = 0; i < n; i++) {
        String **ptr = vector_get(v, i);
        String *s = *ptr;

        if (string_start(s, prefix)) {
            vector_push(filtered, &s);
        }
    }
    return filtered;
}

void insert_no_duplicate(Vector *v, String *aux){
    if(string_size(aux) == 0){
        string_destroy(aux);
        return;
    }

    for (size_t i = 0; i < vector_size(v); i++) {
        String **ptr = vector_get(v, i);
        String *s = *ptr;

        if (string_compare(s,aux) == 0) {
            string_destroy(aux);
            return;
        }
    }

    vector_push(v, &aux);
}

Vector *create_list(size_t dim) {
    Vector *v = vector_create(sizeof(String *), 0);

    for (size_t i = 0; i < dim; i++) {
        String *s = string_create();
        if(!s){
            vector_destroy(v);
            return NULL;
        }
        printf("%zu- ", i + 1);
        string_read(s);

        insert_no_duplicate(v, s);
    }

    return v;
}
