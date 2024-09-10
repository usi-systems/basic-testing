#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_delete) {
    non_new_array_delete ();
    TEST_PASSED;
}


MAIN_TEST_DRIVER (compile, invalid_delete);
