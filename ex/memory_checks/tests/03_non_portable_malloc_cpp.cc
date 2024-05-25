#include "basic_testing.h"
#include <cstdlib>



TEST(compile) {
    TEST_PASSED;
}


TEST(malloc_zero_size) {
    void * p = malloc(0);
    CHECK(p != NULL);
    TEST_PASSED;
}



MAIN_TEST_DRIVER();
