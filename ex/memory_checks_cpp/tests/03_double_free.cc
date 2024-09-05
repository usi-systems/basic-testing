#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_free) {
    double_free ();
    TEST_PASSED;
}


MAIN_TEST_DRIVER (compile, invalid_free);
