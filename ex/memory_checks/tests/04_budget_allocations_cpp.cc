#include "basic_testing.h"
extern "C" {
#include "../array.h"
}



TEST (compile) {
    TEST_PASSED;
}


TEST (no_budget_set) {
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


TEST (zero_budget) {
    MEM_SET_ALLOCATION_BUDGET (0);
    struct array * array = array_new ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (reset_after_budget) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (simple_budget) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    struct array * array2 = array_new ();
    CHECK (array2 == NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (free_increment_budget) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    struct array * array2 = array_new ();
    CHECK (array2 != NULL);
    array_free (array2);
    TEST_PASSED;
}


TEST (budget_realloc_null) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);
    
    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_budget_realloc_null) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);
    
    array_free (array);
    TEST_PASSED;
}


TEST (budget_realloc) {
    MEM_SET_ALLOCATION_BUDGET (2);
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 8; ++i)
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


TEST (reset_after_budget_realloc) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 8; ++i)
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


TEST (malloc_budget_reset) {
    MEM_SET_ALLOCATION_BUDGET (0);
    struct array * array = array_new ();
    CHECK (array == NULL);
    MEM_RESET_ALLOCATOR ();
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_null_budget_reset) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);

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


TEST (realloc_budget_reset) {
    MEM_SET_ALLOCATION_BUDGET (2);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
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


TEST (set_higher_budget) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_SET_ALLOCATION_BUDGET (2);
    for (int i = 8; i < 16; ++i)
	CHECK (array_append (array, i));
    for (int i = 32; i < 32; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_lower_budget) {
    MEM_SET_ALLOCATION_BUDGET (2);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    MEM_SET_ALLOCATION_BUDGET (1);
    array_free (array);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;

}


TEST (zero_budget_calloc) {
    MEM_SET_ALLOCATION_BUDGET (0);
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (simple_budget_calloc) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    struct array * array2 = array_new_calloc ();
    CHECK (array2 == NULL);
    array2 = array_new ();
    CHECK (array2 == NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (reallocarray_budget) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append_reallocarray (array, i));
    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);
    MEM_SET_ALLOCATION_BUDGET (1);
    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    array_free (array);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
