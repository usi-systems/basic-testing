#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

TEST(one_reservation) {
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
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 1);
    CHECK_INT_CMP(r.number, ==, 2);
    CHECK_INT_CMP(t.start, ==, 0);
    TEST_PASSED;
}

TEST(one_reservation_failed) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 2;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 0);

    r.floor = ANY_FLOOR;
    r.number = 1;
    r.capacity = ANY_CAPACITY;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 0);

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 4;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_floor) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 1;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;

    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 1);
    CHECK_INT_CMP(r.number, ==, 2);
    CHECK_INT_CMP(t.start, ==, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_number) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = 2;
    r.capacity = ANY_CAPACITY;

    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 1);
    CHECK_INT_CMP(r.number, ==, 2);
    CHECK_INT_CMP(t.start, ==, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_capacity) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 2;

    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 1);
    CHECK_INT_CMP(r.number, ==, 2);
    CHECK_INT_CMP(t.start, ==, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_all) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;

    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 1);
    CHECK_INT_CMP(r.number, ==, 2);
    CHECK_INT_CMP(t.start, ==, 0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
