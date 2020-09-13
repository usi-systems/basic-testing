#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

TEST(multi_reservation_canceled) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 100;
    t.finish = 1000;
    t.duration = 1;
    make_reservation(&r, &t, "event1");

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 2000;
    t.finish = 3000;
    t.duration = 1;
    make_reservation(&r, &t, "event2");
    CHECK_INT_CMP(cancel_reservation(1, 2, 100), ==, 1);
    CHECK_INT_CMP(cancel_reservation(1, 2, 100), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 2, 2000), ==, 1);
    CHECK_INT_CMP(cancel_reservation(1, 2, 2000), ==, 0);

    TEST_PASSED;
}

TEST(multi_reservation_not_canceled) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 100;
    t.finish = 1000;
    t.duration = 1;
    make_reservation(&r, &t, "event1");

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 2000;
    t.finish = 3000;
    t.duration = 1;
    make_reservation(&r, &t, "event2");
    CHECK_INT_CMP(cancel_reservation(1, 2, 101), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 1, 100), ==, 0);
    CHECK_INT_CMP(cancel_reservation(2, 2, 100), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 2, 2001), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 2, 2001), ==, 0);
    CHECK_INT_CMP(cancel_reservation(2, 1, 2000), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 2, 2001), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 2, 3000), ==, 0);

    clear();

    TEST_PASSED;
}

TEST(multi_canceled_redone) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;

    t.start = 100;
    t.finish = 1000;
    t.duration = 1;

    CHECK_INT_CMP(cancel_reservation(1, 2, 100), ==, 0);
    CHECK_INT_CMP(make_reservation(&r, &t, "event1"), ==, 1);

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 2000;
    t.finish = 3000;
    t.duration = 1;
    CHECK_INT_CMP(make_reservation(&r, &t, "event2"), ==, 1);

    CHECK_INT_CMP(cancel_reservation(1, 2, 2000), ==, 1);
    CHECK_INT_CMP(cancel_reservation(1, 2, 100), ==, 1);
    CHECK_INT_CMP(cancel_reservation(1, 2, 2000), ==, 0);
    CHECK_INT_CMP(cancel_reservation(1, 2, 100), ==, 0);

    TEST_PASSED;
}

int main(int argc, char * argv[]) {
    INIT_TESTING(argc, argv);
    RUN_TEST(multi_reservation_canceled);
    RUN_TEST(multi_reservation_not_canceled);
    RUN_TEST(multi_canceled_redone);

    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
