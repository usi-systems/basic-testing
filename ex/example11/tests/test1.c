#include "basic_testing.h"
#include "../implementation.h"

TEST(initialize) {
    struct foo data;
    int result = init_foo(&data);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(initialize);