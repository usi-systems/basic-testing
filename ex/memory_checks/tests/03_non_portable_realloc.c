#include "basic_testing.h"
#include <stdlib.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (realloc_zero_size) {
    void * p = malloc (10);
    CHECK (p != NULL);

    void * s = realloc (p, 0);
    CHECK (s != NULL);
    
    TEST_PASSED;
}


MAIN_TEST_DRIVER ();
