#include "basic_testing.h"
extern "C" {
#include "../array.h"
}



TEST (compile) {
    TEST_PASSED;
}


TEST (memory_leak) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    CHECK (array_append (array, 1));
    array_free_leak (array);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
