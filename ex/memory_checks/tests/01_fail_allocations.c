#include "basic_testing.h"
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (array_init) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    for (int i = 0; i < 100; ++i)
	CHECK (array_append (array, i));
 
    CHECK_CMP (array_length (array),==,100);
    CHECK_CMP (array_capacity (array),>=,100);

    for (int i = 0; i < 100; ++i)
	CHECK_CMP (array_element (array, i),==,i);
    
    array_free (array);
    TEST_PASSED;
}


TEST (fail_malloc) {
    MEM_FAIL_ALL ();
    struct array * array = array_new ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (reset_after_fail) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_realloc_null) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    MEM_FAIL_ALL ();
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_fail_realloc_null) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);
    
    array_free (array);
    TEST_PASSED;
}


TEST (fail_realloc) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    MEM_FAIL_ALL ();
    for (int i = 4; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_fail_realloc) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    for (int i = 4; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);

    array_free (array);
    TEST_PASSED;
}


TEST (fail_malloc_reset) {
    MEM_FAIL_ALL ();
    struct array * array = array_new ();
    CHECK (array == NULL);
    MEM_RESET_ALLOCATOR ();
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_realloc_null_reset) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    MEM_FAIL_ALL ();
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    MEM_RESET_ALLOCATOR ();
    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);
    
    array_free (array);
    TEST_PASSED;
}


TEST (fail_realloc_reset) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    MEM_FAIL_ALL ();
    for (int i = 4; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    MEM_RESET_ALLOCATOR ();
    for (int i = 4; i < 16; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);
    
    array_free (array);
    TEST_PASSED;
}


TEST (array_init_calloc) {
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    for (int i = 0; i < 100; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,100);
    CHECK_CMP (array_capacity (array),>=,100);

    for (int i = 0; i < 100; ++i)
	CHECK_CMP (array_element (array, i),==,i);

    array_free (array);
    TEST_PASSED;
}


TEST (fail_calloc) {
    MEM_FAIL_ALL ();
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (reset_after_fail_calloc) {
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_reallocarray_null) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    MEM_FAIL_ALL ();
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_fail_reallocarray_null) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    array_free (array);
    TEST_PASSED;
}


TEST (fail_reallocarray) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    MEM_FAIL_ALL ();
    for (int i = 4; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    for (int i = 4; i < 16; ++i)
	CHECK (!array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_fail_reallocarray) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    for (int i = 4; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    for (int i = 4; i < 16; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);

    array_free (array);
    TEST_PASSED;
}


TEST (fail_calloc_reset) {
    MEM_FAIL_ALL ();
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    MEM_RESET_ALLOCATOR ();
    array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_reallocarray_null_reset) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    MEM_FAIL_ALL ();
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    MEM_RESET_ALLOCATOR ();
    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    array_free (array);
    TEST_PASSED;
}


TEST (fail_reallocarray_reset) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    MEM_FAIL_ALL ();
    for (int i = 4; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    for (int i = 4; i < 16; ++i)
	CHECK (!array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    MEM_RESET_ALLOCATOR ();
    for (int i = 4; i < 16; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);

    array_free (array);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
