#include <stdlib.h>

struct foo {
    char *string;
};

struct foo* alloc_foo() {
    struct foo *ptr = malloc(sizeof(struct foo));
    return ptr;
}