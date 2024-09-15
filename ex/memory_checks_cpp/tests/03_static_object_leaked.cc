#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (static_object_ptr) {
    populate_static_vector_ptr ();
    TEST_PASSED;
}




MAIN_TEST_DRIVER ();
