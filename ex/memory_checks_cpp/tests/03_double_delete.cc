#include "basic_testing.h"
#include <cstdlib>
#include "../array.h"


TEST (compile) {
    TEST_PASSED;
}


TEST (invalid_delete) {
    double_delete ();
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
