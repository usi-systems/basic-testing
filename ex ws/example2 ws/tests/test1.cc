#include <sstream>
#include <string>
#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

TEST(empty_reservation_any) {
    clear();
    room r;
    schedule t;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;
    clear();
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 0);
    TEST_PASSED;
}

TEST(empty_reservation_specific) {
    room r;
    schedule t;
    r.floor = 1;
    r.number = 1;
    r.capacity = 0;
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;
    clear();
    CHECK_INT_CMP(make_reservation(&r, &t, "event"), ==, 0);
    TEST_PASSED;
}

TEST(empty_cancel) {
    clear();
    CHECK_INT_CMP(cancel_reservation(0, 0, 0), ==, 0);
    TEST_PASSED;
}

TEST(empty_print_schedule) {
    std::string out;
    std::ostringstream os(out);
    print_schedule(os, 0, 0, 0, 0);
    CHECK_STRING_CMP(out.c_str(),==, "");
    TEST_PASSED;
}

int main(int argc, char * argv[]) {
    INIT_TESTING(argc, argv);
    RUN_TEST(empty_reservation_any);
    RUN_TEST(empty_reservation_specific);
    RUN_TEST(empty_cancel);
    RUN_TEST(empty_print_schedule);
    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
