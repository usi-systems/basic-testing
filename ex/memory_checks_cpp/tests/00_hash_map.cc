#include "basic_testing.h"
#include <cstddef>



TEST (compile) {
    TEST_PASSED;
}


TEST (map_init) {
    CHECK (bt_mem_table == NULL);
    CHECK_CMP (bt_mem_table_size,==,0);
    CHECK_CMP (bt_mem_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_find_empty) {
    int i = 0;
    CHECK (bt_mem_table_find (&i) == NULL);
    TEST_PASSED;
}


TEST (map_insert) {
    int i = 0;

    struct bt_mem_node * ins_node = bt_mem_table_insert (&i);
    CHECK (ins_node != NULL);
    ins_node->size = 12;
    ins_node->allocator = bt_allocator::MALLOC;

    struct bt_mem_node * node = bt_mem_table_find (&i);
    CHECK (node != NULL);
    CHECK_CMP (node->size,==,12);
    CHECK (node->address == &i);
    CHECK_CMP (bt_mem_table_size,==,1);
    CHECK (bt_mem_table_size <= bt_mem_table_capacity);
    bt_mem_table_free ();
    CHECK (bt_mem_table == NULL);
    CHECK_CMP (bt_mem_table_size,==,0);
    CHECK_CMP (bt_mem_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_update) {
    int i = 0;

    struct bt_mem_node * ins_node = bt_mem_table_insert (&i);
    CHECK (ins_node != NULL);
    ins_node->size = 12;
    ins_node->allocator = bt_allocator::MALLOC;

    struct bt_mem_node * node = bt_mem_table_find (&i);
    CHECK (node != NULL);
    CHECK_CMP (node->size,==,12);
    CHECK (node->address == &i);
    CHECK (bt_mem_table_size <= bt_mem_table_capacity);

    size_t capacity = bt_mem_table_capacity;

    ins_node = bt_mem_table_insert (&i);
    ins_node->allocator = bt_allocator::NEW;
    ins_node->size = 15;
    CHECK (node != NULL);
    CHECK_CMP (node->size,==,15);
    CHECK (&i == node->address);
    CHECK_CMP (bt_mem_table_size,==,1);
    CHECK (bt_mem_table_capacity == capacity);

    bt_mem_table_free ();
    CHECK (bt_mem_table == NULL);
    CHECK_CMP (bt_mem_table_size,==,0);
    CHECK_CMP (bt_mem_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_insert_collisions) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	items[i] = i;

    for (size_t i = 0; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK(node != NULL);
	node->allocator = bt_allocator::MALLOC;
	node->size = items[i];
    }

    for (size_t i = 0; i < len; ++i) {
	const struct bt_mem_node * node = bt_mem_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK_CMP (node->allocator,==,bt_allocator::MALLOC);
	CHECK (items + i == node->address);
    }
    CHECK (bt_mem_table_size == len);
    CHECK (bt_mem_table_size <= bt_mem_table_capacity);

    bt_mem_table_free ();
    CHECK (bt_mem_table == NULL);
    CHECK_CMP (bt_mem_table_size,==,0);
    CHECK_CMP (bt_mem_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_update_collisions) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	items[i] = i;

    for (size_t i = 0; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK(node != NULL);
	node->allocator = bt_allocator::MALLOC;
	node->size = items[i];
    }

    for (size_t i = 0; i < len; ++i) {
	const struct bt_mem_node * node = bt_mem_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK_CMP (node->allocator,==,bt_allocator::MALLOC);
	CHECK (items + i == node->address);
    }
    CHECK (bt_mem_table_size == len);
    CHECK (bt_mem_table_size <= bt_mem_table_capacity);
    size_t cap = bt_mem_table_capacity;

    for (size_t i = 0; i < len; ++i)
	items[i] = 2*i;

    for (size_t i = 0; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK(node != NULL);
	node->allocator = bt_allocator::NEW;
	node->size = items[i];
    }

    for (size_t i = 0; i < len; ++i) {
	const struct bt_mem_node * node = bt_mem_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK_CMP (node->allocator,==,bt_allocator::NEW);
	CHECK (items + i == node->address);
    }
    CHECK (bt_mem_table_size == len);
    CHECK (bt_mem_table_capacity == cap);

    bt_mem_table_free ();
    CHECK (bt_mem_table == NULL);
    CHECK_CMP (bt_mem_table_size,==,0);
    CHECK_CMP (bt_mem_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_free) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK (node != NULL);
	node->size = 10;
	node->allocator = bt_allocator::MALLOC;
    }

    bt_mem_table_free ();

    CHECK (bt_mem_table == NULL);
    CHECK_CMP (bt_mem_table_size,==,0);
    CHECK_CMP (bt_mem_table_capacity,==,0);
    TEST_PASSED;
}


TEST (map_remove) {
    int x;
    
    struct bt_mem_node * node = bt_mem_table_insert (&x);
    CHECK (node != NULL);
    node->size = 10;
    node->allocator = bt_allocator::MALLOC;
    CHECK (bt_mem_table_remove (&x));
    CHECK (bt_mem_table_find (&x) == NULL);
    bt_mem_table_free ();
    TEST_PASSED;
}


TEST (map_remove_not_found) {
    int x;

    CHECK (!bt_mem_table_remove (&x));
    CHECK (bt_mem_table_find (&x) == NULL);

    TEST_PASSED;
}


TEST (map_remove_collisions) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK (node != NULL);
	node->size = 10;
	node->allocator = bt_allocator::MALLOC;
    }

    CHECK (bt_mem_table_size == len);
    CHECK (bt_mem_table_size <= bt_mem_table_capacity);
    size_t cap = bt_mem_table_capacity;

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_mem_table_remove (items + i));

    for (size_t i = 0; i < len; ++i)
	CHECK (bt_mem_table_find (items + i) == NULL);

    CHECK (cap > bt_mem_table_capacity);
    
    bt_mem_table_free ();
    TEST_PASSED;
}


TEST (map_remove_collisions_not_found) {
    const size_t len = 1024;
    int items[len];
    int x;

    for (size_t i = 0; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK (node != NULL);
	node->size = 10;
	node->allocator = bt_allocator::MALLOC;
    }

    CHECK (!bt_mem_table_remove (&x));

    bt_mem_table_free ();
    TEST_PASSED;
}


TEST (map_insert_remove_series) {
    const size_t len = 1024;
    int items[len];

    for (size_t i = 0; i < len; ++i)
	items[i] = i;

    for (size_t i = 0; i < len/2; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK (node != NULL);
	node->size = items[i];
	node->allocator = bt_allocator::MALLOC;
    }

    for (size_t i = 0; i < len/2; ++i) {
	const struct bt_mem_node * node = bt_mem_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }
    CHECK (bt_mem_table_size*BT_MEM_TABLE_REHASH_HIGH_RATIO <= bt_mem_table_capacity);
    CHECK (bt_mem_table_size == len/2);

    for (size_t i = 0; i < len/4; ++i) {
	CHECK (bt_mem_table_remove (items + i));
	CHECK (bt_mem_table_find (items + i) == NULL);
    }
    CHECK (bt_mem_table_size*BT_MEM_TABLE_REHASH_HIGH_RATIO <= bt_mem_table_capacity);
    CHECK (bt_mem_table_size == len/4);

    for (size_t i = len/2; i < len; ++i) {
	struct bt_mem_node * node = bt_mem_table_insert (items + i);
	CHECK (node != NULL);
	node->size = items[i];
	node->allocator = bt_allocator::MALLOC;
    }

    for (size_t i = len/2; i < len; ++i) {
	const struct bt_mem_node * node = bt_mem_table_find (items + i);
	CHECK (node != NULL);
	CHECK_CMP (node->size,==,items[i]);
	CHECK (items + i == node->address);
    }
    CHECK (bt_mem_table_size*BT_MEM_TABLE_REHASH_HIGH_RATIO <= bt_mem_table_capacity);
    CHECK (bt_mem_table_size == 3*(len/4));

    for (size_t i = len/4; i < len; ++i) {
	CHECK (bt_mem_table_remove (items + i));
	CHECK (bt_mem_table_find (items + i) == NULL);
    }
    CHECK (bt_mem_table_capacity == BT_MEM_TABLE_MIN_SIZE);
    CHECK (bt_mem_table_size == 0);

    bt_mem_table_free ();
    TEST_PASSED;
}



MAIN_TEST_DRIVER ();
