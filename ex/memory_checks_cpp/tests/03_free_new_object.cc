#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_free) {
    new_object_free ();
    TEST_PASSED;
}



MAIN_TEST_DRIVER();
