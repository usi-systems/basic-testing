#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

void init_ten_rooms() {
    room R[] = {
	{.floor = 1, .number = 3, .capacity = 12},
	{.floor = 1, .number = 4, .capacity = 9},
	{.floor = 1, .number = 5, .capacity = 8},
	{.floor = 1, .number = 6, .capacity = 7},
	{.floor = 1, .number = 7, .capacity = 6},
	{.floor = 3, .number = 3, .capacity = 11},
	{.floor = 3, .number = 4, .capacity = 12},
	{.floor = 3, .number = 5, .capacity = 13},
	{.floor = 3, .number = 6, .capacity = 9},
	{.floor = 3, .number = 7, .capacity = 10}
    };

    clear();

    add_rooms(R, R + 10);
}

TEST(multi_room_multi_time) {
    room r;
    schedule t;
 
    init_ten_rooms();

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 0);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 100);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 30);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 130);

    TEST_PASSED;
}

TEST(multi_room_multi_time_over) {
    room r;
    schedule t;
 
    init_ten_rooms();

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 0);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 100);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 30);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 130);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 60);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 160);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 190);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 220);

    TEST_PASSED;
}

TEST(multi_room_multi_time_over_room) {
    room r;
    schedule t;
 
    init_ten_rooms();

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 0);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 100);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 30);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 130);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 60);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 160);

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 190);

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 11);
    CHECK_INT_CMP(t.start, ==, 220);

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 1);
    CHECK_INT_CMP(r.number, ==, 3);
    CHECK_INT_CMP(r.capacity, ==, 12);
    CHECK_INT_CMP(t.start, ==, 100);

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 1);
    CHECK_INT_CMP(r.floor, ==, 3);
    CHECK_INT_CMP(r.number, ==, 4);
    CHECK_INT_CMP(r.capacity, ==, 12);
    CHECK_INT_CMP(t.start, ==, 100);

    TEST_PASSED;
}

int main(int argc, char * argv[]) {
    INIT_TESTING(argc, argv);
    RUN_TEST(multi_room_multi_time);
    RUN_TEST(multi_room_multi_time_over);
    RUN_TEST(multi_room_multi_time_over_room);

    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
