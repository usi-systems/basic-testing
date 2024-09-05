#include "basic_testing.h"
#include <cstdlib>



TEST (compile) {
    TEST_PASSED;
}


TEST (overflow_calloc) {
    CHECK (calloc (1073741824, 1073741824) == NULL);
    TEST_PASSED;
}


TEST (calloc_zero_nmemb) {
    CHECK (calloc (0, 1073741824) == NULL);
    TEST_PASSED;
}


TEST (calloc_zero_size) {
    CHECK (calloc (1073741824, 0) == NULL);
    TEST_PASSED;
}


TEST (overflow_reallocarray) {
    int * p = (int *) malloc (sizeof (int));
    CHECK (p != NULL);
    CHECK (reallocarray (p, 1073741824, 1073741824) == NULL);
    free (p);
    TEST_PASSED;
}


TEST (reallocarray_zero_nmemb) {
    int * p = (int *) malloc (sizeof (int));
    CHECK (p != NULL);
    CHECK (reallocarray (p, 0, 1073741824) == NULL);
    free (p);
    TEST_PASSED;
}


TEST (reallocarray_zero_size) {
    int * p = (int *) malloc (sizeof (int));
    CHECK (p != NULL);
    CHECK (reallocarray (p, 1073741824, 0) == NULL);
    free (p);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
