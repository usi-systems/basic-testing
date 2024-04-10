#include "basic_testing.h"

TEST(fail) {
    TEST_FAILED;
}

TEST(fail_second) {
    TEST_FAILED;
}

MAIN_TEST_DRIVER(fail, fail_second);