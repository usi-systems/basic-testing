#include "basic_testing.h"
#include <cstdlib>
extern "C" {
#include "../array.h"
}



TEST (compile) {
    TEST_PASSED;
}


TEST (fail_next_malloc_count) {
    bt_mem_schedule_failure (1, 1000);
    struct array * array = array_new ();
    CHECK (array == NULL);
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_malloc_size) {
    bt_mem_schedule_failure (1000, sizeof (struct array));
    struct array * array = array_new ();
    CHECK (array == NULL);
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (malloc_no_failure) {
    bt_mem_schedule_failure (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (malloc_failure_reset) {
    bt_mem_schedule_failure (1, sizeof (struct array));
    bt_mem_cancel_failure ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_realloc_count) {
    bt_mem_schedule_failure (3, 10000);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK (!array_append (array, 10));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_realloc_size) {
    bt_mem_schedule_failure (10000, sizeof (struct array) + sizeof (int)*8 + 1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK (!array_append (array, 10));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_no_failure) {
    bt_mem_schedule_failure (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_failure_reset) {
    bt_mem_schedule_failure (3, sizeof (struct array) + sizeof (int)*8 + 1);
    bt_mem_cancel_failure ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (setting_failure) {
    bt_mem_schedule_failure (1, sizeof (struct array));
    TEST_PASSED;
}


TEST (reset_after_failure) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_calloc_count) {
    bt_mem_schedule_failure (1, 1000);
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_calloc_size) {
    bt_mem_schedule_failure (1000, sizeof (struct array));
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (calloc_no_failure) {
    bt_mem_schedule_failure (0, 0);
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (calloc_failure_reset) {
    bt_mem_schedule_failure (1, sizeof (struct array));
    bt_mem_cancel_failure ();
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_reallocarray_count) {
    bt_mem_schedule_failure (3, 10000);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK (!array_append_reallocarray (array, 10));
    CHECK (array_append_reallocarray (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_reallocarray_size) {
    bt_mem_schedule_failure (10000, sizeof (struct array) + sizeof (int)*8 + 1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));

    CHECK (!array_append_reallocarray (array, 10));
    CHECK (array_append_reallocarray (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (reallocarray_no_failure) {
    bt_mem_schedule_failure (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK (array_append_reallocarray (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (reallocarray_failure_reset) {
    bt_mem_schedule_failure (3, sizeof (struct array) + sizeof (int)*8 + 1);
    bt_mem_cancel_failure ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK (array_append_reallocarray (array, 10));
    array_free (array);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
