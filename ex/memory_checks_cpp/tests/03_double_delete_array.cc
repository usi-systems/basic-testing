#include "basic_testing.h"
#include <cstdlib>
#include "../array.h"


TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_delete) {
    double_delete_array ();
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
