#include "basic_testing.h"
#include "../array.h"
#include <stdlib.h>



TEST(compile) {
    TEST_PASSED;
}


TEST(malloc_add_memory_table) {
    struct array * array = array_new();
    CHECK(array != NULL);

    const struct bt_hash_node *node = bt_memory_table_find(array);
    CHECK(node != NULL);
    CHECK(node->size == sizeof(struct array));

    array_free(array);
    TEST_PASSED;
}


TEST(malloc_fail) {
    BT_FAIL_MEM_ALLOCATIONS;
    struct array * array = array_new();
    CHECK(array == NULL);

    for (int i = 0; i < BT_HASH_TABLE_SIZE; ++i)
	CHECK(bt_memory_table[i] == NULL);

    TEST_PASSED;
}


TEST(free_table_remove) {
    struct array * array = array_new();
    CHECK(array != NULL);
    array_free(array);

    for (int i = 0; i < BT_HASH_TABLE_SIZE; ++i)
	CHECK(bt_memory_table[i] == NULL);
    
    TEST_PASSED;
}


TEST(realloc_map_insert) {
    struct array * array = array_new();
    CHECK(array != NULL);
    CHECK(array_append(array, 1));

    const struct bt_hash_node *node = bt_memory_table_find(array->data);
    CHECK(node != NULL);
    CHECK(node->size == sizeof(int) * array->cap);

    array_free(array);
    TEST_PASSED;
}


TEST(realloc_map_update) {
    struct array * array = array_new();
    CHECK(array != NULL);
    CHECK(array_append(array, 1));
    
    const struct bt_hash_node *node = bt_memory_table_find(array->data);
    CHECK(node != NULL);
    CHECK(node->size == sizeof(int) * array->cap);

    for (int i = 0; i < 100; ++i)
	CHECK(array_append(array, i));

    node = bt_memory_table_find(array->data);
    CHECK(node != NULL);
    CHECK(node->size == sizeof(int) * array->cap);

    array_free(array);
    TEST_PASSED;
}


MAIN_TEST_DRIVER(compile,
		 malloc_add_memory_table,
		 malloc_fail,
		 free_table_remove,
		 realloc_map_insert,
		 realloc_map_update);