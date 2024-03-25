#include <stdlib.h>
#include "alloc.h"

struct foo {
    const char string[10];
};

struct foo* alloc_foo() {
    struct foo *ptr = malloc(sizeof(struct foo));
    return ptr;
}

struct foo* realloc_foo(struct foo *original) {
    struct foo *ptr = realloc(original, sizeof(struct foo));
    return ptr;
}

void dealloc_foo(struct foo *ptr) {
    free(ptr);
}