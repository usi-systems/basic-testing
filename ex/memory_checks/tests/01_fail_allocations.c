#include "basic_testing.h"
#include "../array.h"



TEST(compile) {
    TEST_PASSED;
}


TEST(array_init) {
    struct array * array = array_new();
    CHECK(array != NULL);

    CHECK_CMP(array_length(array),==,0);
    CHECK_CMP(array_capacity(array),==,0);

    for (int i = 0; i < 100; ++i)
	CHECK(array_append(array, i));
 
    CHECK_CMP(array_length(array),==,100);
    CHECK_CMP(array_capacity(array),>=,100);

    for (int i = 0; i < 100; ++i)
	CHECK_CMP(array_element(array, i),==,i);
    
    array_free(array);
    TEST_PASSED;
}


TEST(fail_malloc) {
    BT_FAIL_MEM_ALLOCATIONS;
    struct array * array = array_new();
    CHECK(array == NULL);
    TEST_PASSED;
}


TEST(reset_after_fail) {
    struct array * array = array_new();
    CHECK(array != NULL);
    array_free(array);
    TEST_PASSED;
}


TEST(fail_realloc_null) {
    struct array * array = array_new();
    CHECK(array != NULL);

    BT_FAIL_MEM_ALLOCATIONS;
    for (int i = 0; i < 4; ++i)
	CHECK(!array_append(array, i));

    CHECK_CMP(array_length(array),==,0);
    CHECK_CMP(array_capacity(array),==,0);
    
    array_free(array);
    TEST_PASSED;
}


TEST(reset_after_fail_realloc_null) {
    struct array * array = array_new();
    CHECK(array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,4);
    CHECK_CMP(array_capacity(array),==,8);
    
    array_free(array);
    TEST_PASSED;
}


TEST(fail_realloc) {
    struct array * array = array_new();
    CHECK(array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,4);
    CHECK_CMP(array_capacity(array),==,8);

    BT_FAIL_MEM_ALLOCATIONS;
    for (int i = 4; i < 8; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,8);
    CHECK_CMP(array_capacity(array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK(!array_append(array, i));

    CHECK_CMP(array_length(array),==,8);
    CHECK_CMP(array_capacity(array),==,8);
    
    array_free(array);
    TEST_PASSED;
}


TEST(reset_after_fail_realloc) {
    struct array * array = array_new();
    CHECK(array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,4);
    CHECK_CMP(array_capacity(array),==,8);

    for (int i = 4; i < 8; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,8);
    CHECK_CMP(array_capacity(array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,20);
    CHECK_CMP(array_capacity(array),==,32);

    array_free(array);
    TEST_PASSED;
}


TEST(fail_malloc_reset) {
    BT_FAIL_MEM_ALLOCATIONS;
    struct array * array = array_new();
    CHECK(array == NULL);
    BT_RESET_MEM_ALLOCATOR;
    array = array_new();
    CHECK(array != NULL);
    array_free(array);
    TEST_PASSED;
}


TEST(fail_realloc_null_reset) {
    struct array * array = array_new();
    CHECK(array != NULL);

    BT_FAIL_MEM_ALLOCATIONS;
    for (int i = 0; i < 4; ++i)
	CHECK(!array_append(array, i));

    CHECK_CMP(array_length(array),==,0);
    CHECK_CMP(array_capacity(array),==,0);

    BT_RESET_MEM_ALLOCATOR;
    for (int i = 0; i < 4; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,4);
    CHECK_CMP(array_capacity(array),==,8);
    
    array_free(array);
    TEST_PASSED;
}


TEST(fail_realloc_reset) {
    struct array * array = array_new();
    CHECK(array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,4);
    CHECK_CMP(array_capacity(array),==,8);

    BT_FAIL_MEM_ALLOCATIONS;
    for (int i = 4; i < 8; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,8);
    CHECK_CMP(array_capacity(array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK(!array_append(array, i));

    CHECK_CMP(array_length(array),==,8);
    CHECK_CMP(array_capacity(array),==,8);

    BT_RESET_MEM_ALLOCATOR;
    for (int i = 4; i < 16; ++i)
	CHECK(array_append(array, i));

    CHECK_CMP(array_length(array),==,20);
    CHECK_CMP(array_capacity(array),==,32);
    
    array_free(array);
    TEST_PASSED;
}


MAIN_TEST_DRIVER(compile,
		 array_init,
		 fail_malloc,
		 reset_after_fail,
		 fail_realloc_null,
		 reset_after_fail_realloc_null,
		 fail_realloc,
		 reset_after_fail_realloc,
		 fail_malloc_reset,
		 fail_realloc_null_reset,
		 fail_realloc_reset);
