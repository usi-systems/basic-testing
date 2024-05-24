#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>

void* __real_malloc(size_t);
void __real_free(void*);
void* __real_realloc(void*,size_t);

void *__wrap_malloc(size_t size) {
    printf("fake malloc\n");
    fflush(stdout);
    return __real_malloc(size);
}

void __wrap_free(void * ptr) {
    printf("fake free\n");
    fflush(stdout);
    __real_free(ptr);
}

void *__wrap_realloc(void * ptr, size_t size) {
    printf("fake realloc\n");
    fflush(stdout);
    return __real_realloc(ptr, size);
}

int main() {
    printf("start\n");
    fflush(stdout);
    struct foo* ex = alloc_foo();
    ex = realloc_foo(ex);
    free(ex);
}
