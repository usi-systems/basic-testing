#include "basic_testing.h"
#include "../array.h"
#include <stdlib.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (fail_next_malloc_count) {
    MEM_SCHEDULE_FAILURE (1, 1000);
    struct array * array = array_new ();
    CHECK (array == NULL);
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_malloc_size) {
    MEM_SCHEDULE_FAILURE (1000, sizeof (struct array));
    struct array * array = array_new ();
    CHECK (array == NULL);
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (malloc_no_failure) {
    MEM_SCHEDULE_FAILURE (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (malloc_failure_reset) {
    MEM_SCHEDULE_FAILURE (1, sizeof (struct array));
    MEM_CANCEL_FAILURE ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_realloc_count) {
    MEM_SCHEDULE_FAILURE (3, 10000);
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
    MEM_SCHEDULE_FAILURE (10000, sizeof (struct array) + sizeof (int)*8 + 1);
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
    MEM_SCHEDULE_FAILURE (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_failure_reset) {
    MEM_SCHEDULE_FAILURE (3, sizeof (struct array) + sizeof (int)*8 + 1);
    MEM_CANCEL_FAILURE ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (array_append (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (setting_failure) {
    MEM_SCHEDULE_FAILURE (1, sizeof (struct array));
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
    MEM_SCHEDULE_FAILURE (1, 1000);
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_calloc_size) {
    MEM_SCHEDULE_FAILURE (1000, sizeof (struct array));
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (calloc_no_failure) {
    MEM_SCHEDULE_FAILURE (0, 0);
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (calloc_failure_reset) {
    MEM_SCHEDULE_FAILURE (1, sizeof (struct array));
    MEM_CANCEL_FAILURE ();
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (fail_next_reallocarray_count) {
    MEM_SCHEDULE_FAILURE (3, 10000);
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
    MEM_SCHEDULE_FAILURE (10000, sizeof (struct array) + sizeof (int)*8 + 1);
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
    MEM_SCHEDULE_FAILURE (0, 0);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK (array_append_reallocarray (array, 10));
    array_free (array);
    TEST_PASSED;
}


TEST (reallocarray_failure_reset) {
    MEM_SCHEDULE_FAILURE (3, sizeof (struct array) + sizeof (int)*8 + 1);
    MEM_CANCEL_FAILURE ();
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK (array_append_reallocarray (array, 10));
    array_free (array);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
