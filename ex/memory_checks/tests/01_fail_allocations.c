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
    bt_mem_fail_all ();
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

    bt_mem_fail_all ();
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

    bt_mem_fail_all ();
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
    bt_mem_fail_all ();
    struct array * array = array_new ();
    CHECK (array == NULL);
    bt_mem_reset_allocator ();
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_realloc_null_reset) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    bt_mem_fail_all ();
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    bt_mem_reset_allocator ();
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

    bt_mem_fail_all ();
    for (int i = 4; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    bt_mem_reset_allocator ();
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
    bt_mem_fail_all ();
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

    bt_mem_fail_all ();
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

    bt_mem_fail_all ();
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
    bt_mem_fail_all ();
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    bt_mem_reset_allocator ();
    array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_reallocarray_null_reset) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    bt_mem_fail_all ();
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    bt_mem_reset_allocator ();
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

    bt_mem_fail_all ();
    for (int i = 4; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    for (int i = 4; i < 16; ++i)
	CHECK (!array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    bt_mem_reset_allocator ();
    for (int i = 4; i < 16; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);

    array_free (array);
    TEST_PASSED;
}



MAIN_TEST_DRIVER (compile,
		 array_init,
		 fail_malloc,
		 reset_after_fail,
		 fail_realloc_null,
		 reset_after_fail_realloc_null,
		 fail_realloc,
		 reset_after_fail_realloc,
		 fail_malloc_reset,
		 fail_realloc_null_reset,
		 fail_realloc_reset,
		 array_init_calloc,
		 fail_calloc,
		 reset_after_fail_calloc,
		 fail_reallocarray_null,
		 reset_after_fail_reallocarray_null,
		 fail_reallocarray,
		 reset_after_fail_reallocarray,
		 fail_calloc_reset,
		 fail_reallocarray_null_reset,
		 fail_reallocarray_reset);
