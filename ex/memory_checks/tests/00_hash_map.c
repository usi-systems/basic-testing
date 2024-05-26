#include "basic_testing.h"
#include <string.h>



static size_t find_map_nodes(void) {
    size_t nodes = 0;

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE; ++i)
	for (struct bt_hash_node * p = bt_memory_table[i]; p; p = p->next)
	    ++nodes;

    return nodes;
}


TEST(compile) {
    TEST_PASSED;
}


TEST(map_init) {
    for (size_t i = 0; i < BT_HASH_TABLE_SIZE; ++i)
	CHECK(bt_memory_table[i] == NULL);

    CHECK_CMP(find_map_nodes(),==,0);
    TEST_PASSED;
}


TEST(map_find_empty) {
    int i = 0;
    CHECK(bt_memory_table_find(&i) == NULL);
    CHECK_CMP(find_map_nodes(),==, 0);
    TEST_PASSED;
}


TEST(map_insert) {
    int i = 0;
    void *p;

    CHECK(bt_memory_table_set(&i, 12));

    const struct bt_hash_node * node = bt_memory_table_find(&i);
    CHECK(node != NULL);
    CHECK_CMP(node->size,==,12);
    memcpy(&p, node->address, sizeof(void *));
    CHECK(&i == p);
    CHECK_CMP(find_map_nodes(),==,1);

    bt_memory_table_free();
    CHECK_CMP(find_map_nodes(),==,0);
    TEST_PASSED;
}


TEST(map_update) {
    int i = 0;
    void *p;

    CHECK(bt_memory_table_set(&i, 12));
    const struct bt_hash_node * node = bt_memory_table_find(&i);
    CHECK(node != NULL);
    CHECK_CMP(node->size,==,12);
    memcpy(&p, node->address, sizeof(void *));
    CHECK(&i == p);
    
    CHECK(bt_memory_table_set(&i, 15));
    node = bt_memory_table_find(&i);
    CHECK(node != NULL);
    CHECK_CMP(node->size,==,15);
    memcpy(&p, node->address, sizeof(void *));
    CHECK(&i == p);
    CHECK_CMP(find_map_nodes(),==,1);

    bt_memory_table_free();
    CHECK_CMP(find_map_nodes(),==,0);
    TEST_PASSED;
}


TEST(map_insert_collisions) {
    int items[BT_HASH_TABLE_SIZE*5];

    for (int i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	items[i] = i;

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	CHECK_CMP(bt_memory_table_set(items + i, items[i]),==,1);

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find(items +i);
	void *p;

	CHECK(node != NULL);
	CHECK_CMP(node->size,==,items[i]);
	memcpy(&p, node->address, sizeof(void *));
	CHECK(items + i == p);
    }
    CHECK_CMP(find_map_nodes(),==,5*BT_HASH_TABLE_SIZE);

    bt_memory_table_free();
    CHECK_CMP(find_map_nodes(),==,0);
    TEST_PASSED;
}


TEST(map_update_collisions) {
    int items[BT_HASH_TABLE_SIZE*5];

    for (int i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	items[i] = i;

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	CHECK_CMP(bt_memory_table_set(items + i, items[i]),==,1);

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find(items + i);
	void *p;

	CHECK(node != NULL);
	CHECK_CMP(node->size,==,items[i]);
	memcpy(&p, node->address, sizeof(void *));
	CHECK(items + i == p);
    }
    CHECK_CMP(find_map_nodes(),==,5*BT_HASH_TABLE_SIZE);

    for (int i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	items[i] = 2*i;
    
    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	CHECK_CMP(bt_memory_table_set(items + i, items[i]),==,1);

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i) {
	const struct bt_hash_node * node = bt_memory_table_find(items + i);
	void *p;

	CHECK(node != NULL);
	CHECK_CMP(node->size,==,items[i]);
	memcpy(&p, node->address, sizeof(void *));
	CHECK(items + i == p);
    }
    CHECK_CMP(find_map_nodes(),==,5*BT_HASH_TABLE_SIZE);

    bt_memory_table_free();
    CHECK_CMP(find_map_nodes(),==,0);
    TEST_PASSED;
}



TEST(map_free) {
    int items[BT_HASH_TABLE_SIZE*5];

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE * 5; ++i)
	CHECK(bt_memory_table_set(items + i, 10));

    bt_memory_table_free();

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE; ++i)
	CHECK(bt_memory_table[i] == NULL);

    TEST_PASSED;
}


TEST(map_remove) {
    int x;
    
    CHECK_CMP(bt_memory_table_set(&x, 10),==,1);
    CHECK_CMP(bt_memory_table_remove(&x),==,1);
    CHECK(bt_memory_table_find(&x) == NULL);

    bt_memory_table_free();
    TEST_PASSED;
}


TEST(map_remove_not_found) {
    int x;

    CHECK_CMP(bt_memory_table_remove(&x),==,0);
    CHECK(bt_memory_table_find(&x) == NULL);

    TEST_PASSED;
}


TEST(map_remove_collisions) {
    int items[BT_HASH_TABLE_SIZE*5];

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE*5; ++i)
	CHECK_CMP(bt_memory_table_set(items + i, 10),==,1);

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE*5; ++i)
	CHECK_CMP(bt_memory_table_remove(items + i),==,1);

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE*5; ++i)
	CHECK(bt_memory_table_find(items + i) == NULL);
    
    bt_memory_table_free();
    TEST_PASSED;
}


TEST(map_remove_collisions_not_found) {
    int items[BT_HASH_TABLE_SIZE*5];
    int x;

    for (size_t i = 0; i < BT_HASH_TABLE_SIZE*5; ++i)
	CHECK_CMP(bt_memory_table_set(items + i, 10),==,1);

    CHECK_CMP(bt_memory_table_remove(&x),==,0);

    bt_memory_table_free();
    TEST_PASSED;
}


MAIN_TEST_DRIVER(compile,
		 map_init,
		 map_find_empty,
		 map_insert,
		 map_insert_collisions,
		 map_update_collisions,
		 map_free,
		 map_remove,
		 map_remove_not_found,
		 map_remove_collisions,
		 map_remove_collisions_not_found);
