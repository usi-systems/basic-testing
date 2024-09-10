#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (static_object) {
    populate_static_vector ();
    TEST_PASSED;
}


TEST (static_object_clear) {
    populate_static_vector ();
    clear_static_vector ();
    TEST_PASSED;
}


TEST (static_object_ptr_clear) {
    populate_static_vector_ptr ();
    clear_static_vector_ptr ();
    TEST_PASSED;
}




MAIN_TEST_DRIVER ();
