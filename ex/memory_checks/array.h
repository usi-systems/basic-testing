#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <stddef.h>

struct array {
    int * data;
    size_t len;
    size_t cap;
};

struct array * array_new(void);
void array_free(struct array *);
size_t array_length(struct array *);
size_t array_capacity(struct array *);
int array_element(struct array *, size_t);
int array_append(struct array *, int);

#endif
