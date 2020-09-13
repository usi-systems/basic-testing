#include <sstream>

#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

TEST(compilation) {
    TEST_PASSED;
}

TEST(clear_call) {
    clear();
    TEST_PASSED;
}

TEST(add_rooms_empty) {
    room r;
    r.floor = 0;
    r.number = 0;
    r.capacity = 1;
    add_rooms(&r, &r);
    clear();
    TEST_PASSED;
}

TEST(add_rooms_one) {
    room r;
    r.floor = 0;
    r.number = 0;
    r.capacity = 1;
    room * begin = &r;
    add_rooms(begin, begin + 1);
    clear();
    TEST_PASSED;
}

TEST(make_reservation_call) {
    room r;
    schedule t;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;
    make_reservation(&r, &t, "event");
    TEST_PASSED;
}

TEST(cancel_reservation_call) {
    cancel_reservation(0, 0, 0);
    TEST_PASSED;
}

TEST(print_schedule_call) {
    std::string out;
    std::ostringstream os(out);
    print_schedule(os, 0, 0, 0, 0);
    TEST_PASSED;
}

int main(int argc, char * argv[]) {
    INIT_TESTING(argc, argv);
    RUN_TEST(compilation);
    RUN_TEST(clear_call);
    RUN_TEST(add_rooms_empty);
    RUN_TEST(add_rooms_one);
    RUN_TEST(make_reservation_call);
    RUN_TEST(cancel_reservation_call);
    RUN_TEST(print_schedule_call);
    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
