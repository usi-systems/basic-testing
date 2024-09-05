#include "basic_testing.h"
#include <stdio.h>



TEST (memory_leak) {
    char * name = tempnam (NULL, "somefile");
    CHECK (name != NULL);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (memory_leak);
