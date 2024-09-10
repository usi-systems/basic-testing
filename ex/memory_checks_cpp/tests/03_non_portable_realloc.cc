#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (non_portable_realloc) {
    void * p = malloc (10);
    CHECK (p != NULL);

    void * s = realloc_zero_size (p);
    CHECK (s != NULL);

    TEST_PASSED;
}


MAIN_TEST_DRIVER (compile, non_portable_realloc);
