#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (memory_leak) {
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile, memory_leak);
