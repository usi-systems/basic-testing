#include "basic_testing.h"
#include <stdlib.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (debugger) {
    int result = system ("./tests/05_byte_budget_allocations -d >/dev/null");

    if (result != 0) TEST_FAILED;
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile, debugger);
