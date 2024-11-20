#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_delete) {
    malloc_object_delete ();
    TEST_PASSED;
}



MAIN_TEST_DRIVER();
