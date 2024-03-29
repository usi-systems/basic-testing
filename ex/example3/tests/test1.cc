#include <assert.h>
#include "basic_testing.h"

#include "../stocks.h"

TEST(adding_one) {
    trades_log * l = new_log();
    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,1000), ==, 1);
    delete_log(l);
    TEST_PASSED;
}

TEST(adding_two) {
    trades_log * l = new_log();
    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,1000), ==, 1);
    CHECK_CMP(new_trade(l,2.0,"XYZ",3.4,20), ==, 1);
    delete_log(l);
    TEST_PASSED;
}

TEST(compute_quantity) {
    trades_log * l = new_log();
    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,1000), ==, 1);
    CHECK_CMP(new_trade(l,2.0,"XYZ",3.4,20), ==, 1);
    CHECK_CMP(total_quantity(l), ==, 1020);
    delete_log(l);
    TEST_PASSED;
}

TEST(window_trim) {
    trades_log * l = new_log();
    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,1000), ==, 1);
    CHECK_CMP(new_trade(l,2.0,"XYZ",3.4,20), ==, 1);
    CHECK_CMP(new_trade(l,100.0,"GOOGL",50.0,500), ==, 1);
    CHECK_CMP(total_quantity(l), ==, 500);
    delete_log(l);
    TEST_PASSED;
}

TEST(window_set_and_trim) {
    trades_log * l = new_log();
    CHECK_CMP(new_trade(l,10.0,"GOOGL",40.0,1000), ==, 1);
    CHECK_CMP(new_trade(l,30.0,"XYZ",3.4,20), ==, 1);
    CHECK_CMP(new_trade(l,40.0,"GOOGL",50.0,500), ==, 1);
    set_time_window(l,20);
    CHECK_CMP(total_quantity(l), ==, 520);
    set_time_window(l,30);
    CHECK_CMP(total_quantity(l), ==, 520);
    CHECK_CMP(new_trade(l,50.0,"XYZ",3.4,10), ==, 1);
    CHECK_CMP(total_quantity(l), ==, 530);
    CHECK_CMP(new_trade(l,81.0,"XYZ",3.4,2), ==, 1);
    CHECK_CMP(total_quantity(l), ==, 2);
    delete_log(l);
    TEST_PASSED;
}

TEST(large_trim) {
    trades_log * l = new_log();
    for (double t = 0.0; t <= 1000; t += 5)
	CHECK_CMP(new_trade(l,t,"GOOGL",40.0,1), ==, 1);

    CHECK_CMP(total_quantity(l), ==, 13);
    delete_log(l);
    TEST_PASSED;
}

TEST(large_low_high) {
    trades_log * l = new_log();
    for (double t = 0.0; t <= 1000; t += 5)
	CHECK_CMP(new_trade(l,t,"GOOGL",10 + t,1), ==, 1);

    CHECK_CMP(total_quantity(l), ==, 13);
    CHECK_CMP(high_price(l), ==, 1010);
    CHECK_CMP(low_price(l), ==, 950);
    delete_log(l);
    TEST_PASSED;
}

TEST(clear_quantity) {
    trades_log * l = new_log();
    for (double t = 0.0; t <= 1000; t += 5)
	CHECK_CMP(new_trade(l,t,"GOOGL",10 + t,1), ==, 1);

    clear(l);

    CHECK_CMP(total_quantity(l), ==, 0);

    for (double t = 0.0; t <= 1000; t += 5)
	CHECK_CMP(new_trade(l,t,"GOOGL",10 + t,1), ==, 1);

    CHECK_CMP(total_quantity(l), ==, 13);

    clear(l);

    CHECK_CMP(total_quantity(l), ==, 0);
    delete_log(l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
