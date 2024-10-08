#include "basic_testing.h"
#include <cstdlib>
extern "C" {
#include "../array.h"
}



TEST (compile) {
    TEST_PASSED;
}


TEST (malloc_add_memory_table) {
    struct array * array = array_new();
    CHECK (array != NULL);

    const struct bt_mem_node *node = bt_mem_table_find (array);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(struct array));

    array_free (array);
    TEST_PASSED;
}


TEST (malloc_fail) {
    bt_mem_fail_all ();
    struct array * array = array_new ();
    CHECK (array == NULL);
    CHECK (bt_mem_table_size == 0);
    TEST_PASSED;
}


TEST (free_table_remove) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    CHECK (bt_mem_table_size == 0);
    TEST_PASSED;
}


TEST (realloc_map_insert) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    CHECK (array_append (array, 1));

    const struct bt_mem_node *node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(int) * array->cap);
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_map_update) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    CHECK (array_append(array, 1));
    
    const struct bt_mem_node *node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(int) * array->cap);

    for (int i = 0; i < 100; ++i)
	CHECK (array_append(array, i));

    node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(int) * array->cap);

    array_free (array);
    TEST_PASSED;
}


TEST (calloc_add_memory_table) {
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);

    const struct bt_mem_node *node = bt_mem_table_find (array);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(struct array));

    array_free (array);
    TEST_PASSED;
}


TEST (calloc_fail) {
    bt_mem_fail_all ();
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);

    CHECK (bt_mem_table_size == 0);
    TEST_PASSED;
}


TEST (reallocarray_map_insert) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    CHECK (array_append_reallocarray (array, 1));

    const struct bt_mem_node *node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof (int) * array->cap);

    array_free (array);
    TEST_PASSED;
}


TEST (reallocarray_map_update) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    CHECK (array_append_reallocarray (array, 1));

    const struct bt_mem_node *node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof (int) * array->cap);

    for (int i = 0; i < 100; ++i)
	CHECK (array_append_reallocarray (array, i));

    node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof (int) * array->cap);

    array_free (array);
    TEST_PASSED;
}


MAIN_TEST_DRIVER ();
