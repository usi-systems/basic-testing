#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (non_portable_malloc) {
    void * p = malloc_zero_size ();
    CHECK (p != NULL);
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile, non_portable_malloc);
