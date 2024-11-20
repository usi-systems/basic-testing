#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_free) {
    non_malloc_free ();
    TEST_PASSED;
}


MAIN_TEST_DRIVER (compile, invalid_free);
