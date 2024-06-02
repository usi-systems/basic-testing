#include "basic_testing.h"
#include "../implementation.h"

TEST(compile) {
    TEST_PASSED;
}

TEST(with_variable) {
    int variable = 0;
    variable++;
    TEST_PASSED;
}

MAIN_TEST_DRIVER(compile, with_variable);
