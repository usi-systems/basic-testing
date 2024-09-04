#include "basic_testing.h"
#include <cstring>



TEST (memory_leak) {
    const char * str = "testing";
    char * str2 = strdup(str);

    CHECK_CMP(strcmp(str, str2),==,0);

    TEST_PASSED;
}

MAIN_TEST_DRIVER ();
