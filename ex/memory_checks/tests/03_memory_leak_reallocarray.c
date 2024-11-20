#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (memory_leak) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    CHECK (array_append_reallocarray (array, 1));
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile, memory_leak);
