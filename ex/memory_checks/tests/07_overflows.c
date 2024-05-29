#include "basic_testing.h"
#include <stdlib.h>


TEST (compile) {
    TEST_PASSED;
}


TEST (overflow_calloc) {
    CHECK (calloc (1073741824, 1073741824) == NULL);
    TEST_PASSED;
}


TEST (overflow_reallocarray) {
    int * p = malloc(sizeof(int));
    CHECK (p != NULL);
    CHECK (reallocarray (p, 1073741824, 1073741824) == NULL);
    free (p);
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile,
		  overflow_calloc,
		  overflow_reallocarray);
