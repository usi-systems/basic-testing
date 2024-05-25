#include "basic_testing.h"
#include <stdlib.h>

TEST(compile) {
    TEST_PASSED;
}

TEST(malloc_zero_size) {
    void * p = malloc(0);
    CHECK(p != NULL);
    TEST_PASSED;
}



MAIN_TEST_DRIVER(compile, malloc_zero_size);
