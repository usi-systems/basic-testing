#include "array.h"
#include <stddef.h>
#include <stdlib.h>


static size_t initial_cap = 8;


struct array * array_new(void) {
    struct array * a = malloc(sizeof(struct array));
    if (!a) return NULL;

    a->data = NULL;
    a->len = 0;
    a->cap = 0;
    return a;
}

struct array * array_new_calloc(void)
{
    return calloc(1, sizeof(struct array));
}

void array_free(struct array * array) {
    if (array->cap) free(array->data);
    free(array);
}

void array_free_leak(struct array * array) {
    free(array);
}


size_t array_length(struct array * array) {
    return array->len;
}

size_t array_capacity(struct array * array) {
    return array->cap;
}

int array_element(struct array * array, size_t index) {
    return array->data[index];
}

int array_append(struct array * array, int element) {
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

int array_append_reallocarray(struct array * array, int element) {
    if (array->len == array->cap) {
	size_t new_cap = array->cap ? 2*array->cap : initial_cap;

	int * new_data = reallocarray(array->data, new_cap, sizeof(int));
	if (!new_data) return 0;

	array->data = new_data;
	array->cap = new_cap;
    }

    array->data[array->len++] = element;
    return 1;
}
