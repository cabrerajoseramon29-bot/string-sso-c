#ifndef FILTERS_H
#define FILTERS_H

#include "../core/vector/vector.h"
#include "../core/string/string_sso.h"

Vector *filter_by_length(Vector *v);
Vector *filter_by_exact_length(Vector *v, size_t len);
Vector *filter_by_prefix(Vector *v, const String *prefix);

void insert_no_duplicate(Vector *v, String *aux);

Vector *create_list(size_t dim);

#endif