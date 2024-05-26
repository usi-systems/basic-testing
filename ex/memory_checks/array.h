#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <stddef.h>

struct array {
    int * data;
    size_t len;
    size_t cap;
};

struct array * array_new(void);
void array_free(struct array * array);
void array_free_leak(struct array * array);
size_t array_length(struct array * array);
size_t array_capacity(struct array * array);
int array_element(struct array * array, size_t index);
int array_append(struct array * array, int value);

#endif
