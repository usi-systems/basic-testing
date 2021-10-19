#include <assert.h>
#include <string.h>
#include "basic_testing.h"

#include "../stocks.h"

TEST(good_and_bad_times) {
    trades_log * l = new_log();

    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,100), ==, 1);
    CHECK_CMP(new_trade(l,1.0,"XYZ",1000.0,200), ==, 1);
    CHECK_CMP(new_trade(l,0.5,"XYZ",1000.0,350), ==, 0);
    CHECK_CMP(new_trade(l,0.6,"XYZ",1000.0,350), ==, 0);
    CHECK_CMP(total_quantity(l), ==, 300);
    delete_log(l);
    TEST_PASSED;
}

TEST(good_clear_good_times) {
    trades_log * l = new_log();

    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,100), ==, 1);
    CHECK_CMP(new_trade(l,1.0,"XYZ",1000.0,200), ==, 1);
    clear(l);
    CHECK_CMP(new_trade(l,0.5,"XYZ",1000.0,350), ==, 1);
    CHECK_CMP(total_quantity(l), ==, 350);
    delete_log(l);
    TEST_PASSED;
}

TEST(good_and_bad_prices) {
    trades_log * l = new_log();

    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,100), ==, 1);
    CHECK_CMP(new_trade(l,1.0,"XYZ",1000.0,200), ==, 1);
    CHECK_CMP(new_trade(l,0.5,"XYZ",0,350), ==, 0);
    CHECK_CMP(new_trade(l,0.5,"XYZ",-1,350), ==, 0);
    CHECK_CMP(total_quantity(l), ==, 300);
    delete_log(l);
    TEST_PASSED;
}

TEST(good_and_bad_quantities) {
    trades_log * l = new_log();

    CHECK_CMP(new_trade(l,1.0,"GOOGL",40.0,100), ==, 1);
    CHECK_CMP(new_trade(l,1.0,"XYZ",1000.0,200), ==, 1);
    CHECK_CMP(new_trade(l,0.5,"XYZ",200,-20), ==, 0);
    CHECK_CMP(new_trade(l,0.5,"XYZ",400,-10), ==, 0);
    CHECK_CMP(total_quantity(l), ==, 300);
    delete_log(l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER()

