#include "array.h"
#include <stddef.h>
#include <stdlib.h>


static size_t initial_cap = 8;


struct array * array_new (void) {
    struct array * a = malloc(sizeof(struct array));
    if (!a) return NULL;

    a->data = NULL;
    a->len = 0;
    a->cap = 0;
    return a;
}

struct array * array_new_calloc (void) {
    return calloc(1, sizeof(struct array));
}

void array_free (struct array * array) {
    if (array->cap) free(array->data);
    free(array);
}

void array_free_leak (struct array * array) {
    free(array);
}

size_t array_length (struct array * array) {
    return array->len;
}

size_t array_capacity (struct array * array) {
    return array->cap;
}

int array_element (struct array * array, size_t index) {
    return array->data[index];
}

int array_append (struct array * array, int element) {
    if (array->len == array->cap) {
	size_t new_cap = array->cap ? 2*array->cap : initial_cap;

	int * new_data = realloc(array->data, new_cap*sizeof(int));
	if (!new_data) return 0;

	array->data = new_data;
	array->cap = new_cap;
    }

    array->data[array->len++] = element;
    return 1;
}

int array_append_reallocarray (struct array * array, int element) {
    if (array->len == array->cap) {
	size_t new_cap = array->cap ? 2*array->cap : initial_cap;

#ifdef __APPLE__
	int * new_data = realloc (array->data, new_cap*sizeof(int));
#else
	int * new_data = reallocarray (array->data, new_cap, sizeof(int));
#endif
	if (!new_data) return 0;

	array->data = new_data;
	array->cap = new_cap;
    }

    array->data[array->len++] = element;
    return 1;
}

void double_free (void) {
    int a = 10;
    void * p = malloc (10);
    if (a < 20) free (p);
    free (p);
}

void non_malloc_free (void) {
    int a = 10;
    int * p = NULL;
    if (a < 20) p = &a;
    free (p);
}

void * malloc_zero_size (void) {
    return malloc (0);
}

void * realloc_zero_size (void * ptr) {
    return realloc (ptr, 0);
}
