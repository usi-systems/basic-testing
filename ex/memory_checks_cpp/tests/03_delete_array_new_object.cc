#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_delete_array) {
    new_object_delete_array ();
    TEST_PASSED;
}



MAIN_TEST_DRIVER();
