#include "basic_testing.h"
#include <cstdlib>


TEST (compile) {
    TEST_PASSED;
}


TEST (overflow_calloc) {
    CHECK (calloc (1073741824, 1073741824) == NULL);
    TEST_PASSED;
}


TEST (overflow_reallocarray) {
    int * p = (int *) malloc(sizeof(int));
    CHECK (p != NULL);
    CHECK (reallocarray (p, 1073741824, 1073741824) == NULL);
    free (p);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
