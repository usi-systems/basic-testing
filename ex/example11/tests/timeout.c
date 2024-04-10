#include "basic_testing.h"
#include <unistd.h>


TEST(timeout) {
    sleep(10);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(timeout);