#include "basic_testing.h"
#include <string.h>



TEST (compile) {
    TEST_PASSED;
}


TEST (map_init) {
    CHECK (bt_memory_table == NULL);
    CHECK_CMP (bt_memory_table_size,==,0);
    CHECK_CMP (bt_memory_table_capacity,==,0);
    TEST_PASSED;
}


TEST(map_find_empty) {
    int i = 0;
    CHECK (bt_memory_table_find (&i) == NULL);
    TEST_PASSED;
}


TEST (map_insert) {
    int i = 0;

    CHECK (bt_memory_table_set (&i, 12));

    struct bt_hash_node * node = bt_memory_table_find (&i);
    CHECK (node != NULL);
    CHECK_CMP (node->size,==,12);
    CHECK (node->address == &i);
    CHECK_CMP (bt_memory_table_size,==,1);
    CHECK (bt_memory_table_size <= bt_memory_table_capacity);
    bt_memory_table_free ();
    CHECK (bt_memory_table == NULL);
    CHECK_CMP (bt_memory_table_size,==,0);
    CHECK_CMP (bt_memory_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_update) {
    int i = 0;

    CHECK (bt_memory_table_set (&i, 12));
    struct bt_hash_node * node = bt_memory_table_find (&i);
    CHECK (node != NULL);
    CHECK_CMP (node->size,==,12);
    CHECK (node->address == &i);
    CHECK (bt_memory_table_size <= bt_memory_table_capacity);

    size_t capacity = bt_memory_table_capacity;

    CHECK (bt_memory_table_set (&i, 15));
    node = bt_memory_table_find (&i);
    CHECK (node != NULL);
    CHECK_CMP (node->size,==,15);
    CHECK (&i == node->address);
    CHECK_CMP (bt_memory_table_size,==,1);
    CHECK (bt_memory_table_capacity == capacity);

    bt_memory_table_free ();
    CHECK (bt_memory_table == NULL);
    CHECK_CMP (bt_memory_table_size,==,0);
    CHECK_CMP (bt_memory_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_insert_collisions) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	items[i] = i;

    for (size_t i = 0; i < len; ++i)
	CHECK_CMP (bt_memory_table_set (items + i, items[i]),==,1);

    for (size_t i = 0; i < len; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }
    CHECK (bt_memory_table_size == len);
    CHECK (bt_memory_table_size <= bt_memory_table_capacity);

    bt_memory_table_free ();
    CHECK (bt_memory_table == NULL);
    CHECK_CMP (bt_memory_table_size,==,0);
    CHECK_CMP (bt_memory_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_update_collisions) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	items[i] = i;

    for (size_t i = 0; i < len; ++i)
	CHECK_CMP (bt_memory_table_set (items + i, items[i]),==,1);

    for (size_t i = 0; i < len; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }
    CHECK (bt_memory_table_size == len);
    CHECK (bt_memory_table_size <= bt_memory_table_capacity);
    size_t cap = bt_memory_table_capacity;

    for (size_t i = 0; i < len; ++i)
	items[i] = 2*i;
    
    for (size_t i = 0; i < len; ++i)
	CHECK_CMP (bt_memory_table_set (items + i, items[i]),==,1);

    for (size_t i = 0; i < len; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }
    CHECK (bt_memory_table_size == len);
    CHECK (bt_memory_table_capacity == cap);


    bt_memory_table_free ();
    CHECK (bt_memory_table == NULL);
    CHECK_CMP (bt_memory_table_size,==,0);
    CHECK_CMP (bt_memory_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_free) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_memory_table_set (items + i, 10));

    bt_memory_table_free();

    CHECK (bt_memory_table == NULL);
    CHECK_CMP (bt_memory_table_size,==,0);
    CHECK_CMP (bt_memory_table_capacity,==,0);
    TEST_PASSED;
}


TEST(map_remove) {
    int x;
    
    CHECK (bt_memory_table_set (&x, 10));
    CHECK (bt_memory_table_remove (&x));
    CHECK (bt_memory_table_find (&x) == NULL);
    bt_memory_table_free ();
    TEST_PASSED;
}


TEST(map_remove_not_found) {
    int x;

    CHECK (!bt_memory_table_remove (&x));
    CHECK (bt_memory_table_find(&x) == NULL);

    TEST_PASSED;
}


TEST(map_remove_collisions) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_memory_table_set (items + i, 10));

    CHECK (bt_memory_table_size == len);
    CHECK (bt_memory_table_size <= bt_memory_table_capacity);
    size_t cap = bt_memory_table_capacity;

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_memory_table_remove (items + i));

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_memory_table_find (items + i) == NULL);

    CHECK (cap > bt_memory_table_capacity);
    
    bt_memory_table_free();
    TEST_PASSED;
}


TEST(map_remove_collisions_not_found) {
    const size_t len = 1024;
    int items[len];
    int x;

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_memory_table_set (items + i, 10));

    CHECK (!bt_memory_table_remove(&x));

    bt_memory_table_free();
    TEST_PASSED;
}


TEST(map_insert_remove_series) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	items[i] = i;

    for (size_t i = 0; i < len/2; ++i)
	CHECK (bt_memory_table_set (items + i, items[i]));

    for (size_t i = 0; i < len/2; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }

    for (size_t i = 0; i < len/4; ++i) {
	CHECK (bt_memory_table_remove (items + i));
	CHECK (bt_memory_table_find (items + i) == NULL);
    }
    
    for (size_t i = len/2; i < len; ++i)
	CHECK (bt_memory_table_set (items + i, items[i]));

    for (size_t i = len/2; i < len; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }

    for (size_t i = len/4; i < len; ++i) {
	CHECK (bt_memory_table_remove (items + i));
	CHECK (bt_memory_table_find (items + i) == NULL);
    }

    bt_memory_table_free();
    TEST_PASSED;
}


MAIN_TEST_DRIVER(compile,
		 map_init,
		 map_find_empty,
		 map_insert,
		 map_update,
		 map_insert_collisions,
		 map_update_collisions,
		 map_free,
		 map_remove,
		 map_remove_not_found,
		 map_remove_collisions,
		 map_remove_collisions_not_found,
		 map_insert_remove_series);
