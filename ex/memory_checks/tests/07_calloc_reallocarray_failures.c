#include "basic_testing.h"
#include <stdlib.h>
#include "../array.h"


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
    int * p = malloc (sizeof (int));
    CHECK (p != NULL);
    CHECK (wrapped_reallocarray (p, 1073741824, 1073741824) == NULL);
    free (p);
    TEST_PASSED;
}


TEST (reallocarray_zero_nmemb) {
    int * p = malloc (sizeof (int));
    CHECK (p != NULL);
    CHECK (wrapped_reallocarray (p, 0, 1073741824) == NULL);
    free (p);
    TEST_PASSED;
}


TEST (reallocarray_zero_size) {
    int * p = malloc (sizeof (int));
    CHECK (p != NULL);
    CHECK (wrapped_reallocarray (p, 1073741824, 0) == NULL);
    free (p);
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile,
		  overflow_calloc,
		  calloc_zero_nmemb,
		  calloc_zero_size,
		  overflow_reallocarray,
		  reallocarray_zero_nmemb,
		  reallocarray_zero_size);
