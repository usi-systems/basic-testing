#include "basic_testing.h"
#include "../array.h"
#include <stdlib.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (fail_next_malloc_count) {
    bt_malloc_schedule_failure (1, 0);
    struct array * array = array_new ();
    CHECK (array == NULL);
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_malloc_size) {
    bt_malloc_schedule_failure (0, sizeof(struct array));
    struct array * array = array_new ();
    CHECK (array == NULL);
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (malloc_no_failure) {
    bt_malloc_schedule_failure (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (malloc_failure_reset) {
    bt_malloc_schedule_failure (1, sizeof(struct array));
    bt_malloc_cancel_failure ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_realloc_count) {
    bt_malloc_schedule_failure (3, 0);
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
    bt_malloc_schedule_failure (0, sizeof(struct array) + sizeof(int)*8 + 1);
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
    bt_malloc_schedule_failure (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_failure_reset) {
    bt_malloc_schedule_failure (3, sizeof(struct array) + sizeof(int)*8 + 1);
    bt_malloc_cancel_failure ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (setting_failure) {
    bt_malloc_schedule_failure (1, sizeof(struct array));
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


MAIN_TEST_DRIVER(compile,
		 fail_next_malloc_count,
		 fail_next_malloc_size,
		 malloc_no_failure,
		 malloc_failure_reset,
		 fail_next_realloc_count,
		 fail_next_realloc_size,
		 realloc_no_failure,
		 realloc_failure_reset,
		 setting_failure,
		 reset_after_failure);
