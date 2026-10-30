#include "basic_testing.h"
#include <stdlib.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_free) {
    int a = 10;
    void * p = malloc (10);
    if (a < 20) free (p);
    free (p);
    TEST_PASSED;
}


MAIN_TEST_DRIVER ();
