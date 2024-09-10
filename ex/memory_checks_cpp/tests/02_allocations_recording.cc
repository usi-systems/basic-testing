#include "basic_testing.h"
#include <cstdlib>
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (malloc_add_memory_table) {
    struct array * array = array_new();
    CHECK (array != NULL);

    const struct bt_mem_node *node = bt_mem_table_find (array);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(struct array));
    CHECK (node->allocator == bt_allocator::MALLOC);
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
    CHECK (node->allocator == bt_allocator::MALLOC);
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
    CHECK (node->allocator == bt_allocator::MALLOC);
    for (int i = 0; i < 100; ++i)
	CHECK (array_append(array, i));

    node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(int) * array->cap);
    CHECK (node->allocator == bt_allocator::MALLOC);
    array_free (array);
    TEST_PASSED;
}


TEST (calloc_add_memory_table) {
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);

    const struct bt_mem_node *node = bt_mem_table_find (array);
    CHECK (node != NULL);
    CHECK (node->size == sizeof(struct array));
    CHECK (node->allocator == bt_allocator::MALLOC);
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
    CHECK (node->allocator == bt_allocator::MALLOC);
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
    CHECK (node->allocator == bt_allocator::MALLOC);
    for (int i = 0; i < 100; ++i)
	CHECK (array_append_reallocarray (array, i));

    node = bt_mem_table_find (array->data);
    CHECK (node != NULL);
    CHECK (node->size == sizeof (int) * array->cap);
    CHECK (node->allocator == bt_allocator::MALLOC);
    array_free (array);
    TEST_PASSED;
}


TEST (new_add_memory_table) {
    array_cpp * array = array_cpp_new();
    CHECK (array != nullptr);
    const struct bt_mem_node *node = bt_mem_table_find (array);
    CHECK (node != nullptr);
    CHECK (node->size >= sizeof(struct array));
    CHECK (node->allocator == bt_allocator::NEW);
    array_cpp_delete (array);
    TEST_PASSED;
}


TEST (new_fail) {
    MEM_FAIL_ALL ();
    try {
	array_cpp * array = array_cpp_new ();
	array_cpp_delete (array);
    } catch (const std::bad_alloc& e) {
	CHECK (bt_mem_table_size == 0);
	TEST_PASSED;
    }
    TEST_FAILED;
}


TEST (delete_table_remove) {
    array_cpp * array = array_cpp_new();
    CHECK (array != nullptr);
    array_cpp_delete (array);
    CHECK (bt_mem_table_size == 0);
    TEST_PASSED;
}


TEST (new_array_add_memory_table) {
    array_cpp array;
    array.append(10);
    const struct bt_mem_node *node = bt_mem_table_find ((void *) array.get_data());
    CHECK (node != nullptr);
    CHECK (node->size >= sizeof(struct array));
    CHECK (node->allocator == bt_allocator::NEW_ARRAY);
    TEST_PASSED;
}


TEST (new_array_fail) {
    MEM_FAIL_ALL ();
    try {
	array_cpp array;
	array.append(10);
    } catch (const std::bad_alloc& e) {
	CHECK (bt_mem_table_size == 0);
	TEST_PASSED;
    }
    TEST_FAILED;
}


TEST (delete_array_table_remove) {
    {
	array_cpp array;
	for (int i = 0; i < 100; ++i)
	    array.append(i);
    }

    CHECK (bt_mem_table_size == 0);
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
















// TEST (set_higher_budget_malloc) {
//     MEM_SET_ALLOCATION_BUDGET (1);
//     struct array * array = array_new ();
//     CHECK (array != NULL);
//     for (int i = 0; i < 8; ++i)
// 	CHECK (!array_append (array, i));
//     MEM_SET_ALLOCATION_BUDGET (2);
//     for (int i = 8; i < 16; ++i)
// 	CHECK (array_append (array, i));
//     for (int i = 32; i < 32; ++i)
// 	CHECK (!array_append (array, i));
//     array_free (array);
//     array = array_new ();
//     CHECK (array != NULL);
//     for (int i = 0; i < 8; ++i)
// 	CHECK (array_append (array, i));
//     for (int i = 8; i < 16; ++i)
// 	CHECK (!array_append (array, i));
//     array_free (array);
//     TEST_PASSED;
// }
