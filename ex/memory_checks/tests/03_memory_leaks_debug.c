#include "basic_testing.h"
#include <stdlib.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (debugger) {
    int result = system ("./tests/03_memory_leaks -d >/dev/null");

    if (result != 0) TEST_FAILED;
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile, debugger);
