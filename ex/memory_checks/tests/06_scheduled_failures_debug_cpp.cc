#include "basic_testing.h"
#include <cstdlib>



TEST (compile) {
    TEST_PASSED;
}


TEST (debugger) {
    int result = system ("./tests/06_scheduled_failures_cpp -d >/dev/null");

    if (result != 0) TEST_FAILED;
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
