#include <stdlib.h>
#include <stdio.h>
#include "alloc.h"

struct foo {
    int a;
};

struct foo* alloc_foo() {
    struct foo *ptr = malloc(sizeof(struct foo));
    if (ptr == NULL) {printf("INVALID malloc"); fflush(stdout);};

    return ptr;
}

struct foo* realloc_foo(struct foo *original) {
    struct foo *ptr = realloc(original, sizeof(struct foo));
    if (ptr == NULL) {printf("INVALID realloc"); fflush(stdout);};
    return ptr;
}

void dealloc_foo(struct foo *ptr) {
    free(ptr);
}
