#include "basic_testing.h"

TEST(fail) {
    int result = 0;
    TEST_FAILED;
}

TEST(fail_second) {
    TEST_FAILED;
}

MAIN_TEST_DRIVER(fail, fail_second);
