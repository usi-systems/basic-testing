#include "basic_testing.h"

TEST(compile) {
    TEST_PASSED;
}

TEST(set_init) {
    struct bt_hash_set set;

    bt_hash_set_init(&set);
    for (size_t i = 0; i < BT_HASH_TABLE_SIZE; ++i)
	CHECK(set.table[i] == NULL);
    bt_hash_set_delete(&set);

    TEST_PASSED;
}

TEST(set_empty) {
    struct bt_hash_set set;

    bt_hash_set_init(&set);
    CHECK_CMP(bt_hash_set_size(&set),==,0);
    bt_hash_set_delete(&set);

    TEST_PASSED;
}

TEST(set_insert) {
    int i = 0;
    struct bt_hash_set set;

    bt_hash_set_init(&set);
    CHECK_CMP(bt_hash_set_insert(&set, &i),==,1);
    CHECK_CMP(bt_hash_set_size(&set),==,1);
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_insert_duplicate) {
    int i = 0;
    struct bt_hash_set set;

    bt_hash_set_init(&set);
    CHECK_CMP(bt_hash_set_insert(&set, &i),==,1);
    CHECK_CMP(bt_hash_set_size(&set),==,1);
    CHECK_CMP(bt_hash_set_insert(&set, &i),==,0);
    CHECK_CMP(bt_hash_set_size(&set),==,1);
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_insert_collisions) {
    int items[BT_HASH_TABLE_SIZE*5];
    struct bt_hash_set set;
    
    bt_hash_set_init(&set);

    for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
	CHECK_CMP(bt_hash_set_insert(&set, items + i),==,1);

    CHECK(bt_hash_set_size(&set) == sizeof(items)/sizeof(int));
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_insert_collisions_duplicate) {
    int items[BT_HASH_TABLE_SIZE*5];
    struct bt_hash_set set;
    
    bt_hash_set_init(&set);

    for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
	CHECK_CMP(bt_hash_set_insert(&set, items + i),==,1);

    CHECK(bt_hash_set_size(&set) == sizeof(items)/sizeof(int));

    for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
	CHECK_CMP(bt_hash_set_insert(&set, items + i),==,0);

    CHECK(bt_hash_set_size(&set) == sizeof(items)/sizeof(int));
    
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_remove) {
    int x;
    struct bt_hash_set set;
    
    bt_hash_set_init(&set);

    bt_hash_set_init(&set);
    CHECK_CMP(bt_hash_set_insert(&set, &x),==,1);
    CHECK_CMP(bt_hash_set_remove(&set, &x),==,1);
    CHECK_CMP(bt_hash_set_size(&set),==,0);
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_remove_not_found) {
    struct bt_hash_set set;
    int i;

    bt_hash_set_init(&set);
    CHECK_CMP(bt_hash_set_remove(&set, &i),==,0);
    CHECK_CMP(bt_hash_set_size(&set),==,0);
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_remove_collisions) {
    int items[BT_HASH_TABLE_SIZE*5];
    struct bt_hash_set set;
    
    bt_hash_set_init(&set);

    for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
	CHECK_CMP(bt_hash_set_insert(&set, items + i),==,1);

    CHECK(bt_hash_set_size(&set) == sizeof(items)/sizeof(int));

    for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
	CHECK_CMP(bt_hash_set_remove(&set, items + i),==,1);

    CHECK(bt_hash_set_size(&set) == 0);
    
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}

TEST(set_remove_collisions_not_found) {
    int items[BT_HASH_TABLE_SIZE*5];
    int x;
    struct bt_hash_set set;
    
    bt_hash_set_init(&set);

    for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
	CHECK_CMP(bt_hash_set_insert(&set, items + i),==,1);

    CHECK(bt_hash_set_size(&set) == sizeof(items)/sizeof(int));
    CHECK_CMP(bt_hash_set_remove(&set, &x),==,0);
    CHECK(bt_hash_set_size(&set) == sizeof(items)/sizeof(int));
    bt_hash_set_delete(&set);
    
    TEST_PASSED;
}


MAIN_TEST_DRIVER(compile,
		 set_init,
		 set_empty,
		 set_insert,
		 set_insert_duplicate,
		 set_insert_collisions,
		 set_insert_collisions_duplicate,
		 set_remove,
		 set_remove_not_found,
		 set_remove_collisions,
		 set_remove_collisions_not_found);
