#include "../core/vector/vector.h"
#include "../core/string/string_sso.h"
#include <stddef.h>

void insertion_sort_strings(Vector *v) {
    if (vector_size(v) < 2) return;

    size_t n = vector_size(v);

    for (size_t i = 1; i < n; i++) {
        String **ptr = vector_get(v, i);
        String *key = *ptr;

        size_t j = i;

        while (j > 0) {
            String **ptr2 = vector_get(v, j-1);
            String *temp = *ptr2;
            if (string_compare(temp, key) > 0) {
                vector_set(v, j, &temp);
            } else {
                break;
            }
            j--;
        }

        vector_set(v, j, &key);
    }
}