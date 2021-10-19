#include <assert.h>
#include "basic_testing.h"

#include "../stocks.h"

TEST(compilation) {
    TEST_PASSED;
}

TEST(constructor_destructor) {
    trades_log * l = new_log();
    delete_log(l);
    TEST_PASSED;
}

TEST(clear_call) {
    trades_log * l = new_log();
    clear(l);
    delete_log(l);
    TEST_PASSED;
}

TEST(empty_log) {
    trades_log * l = new_log();
    CHECK_CMP(total_quantity(l), ==, 0);
    CHECK_CMP(high_price(l), ==, 0);
    CHECK_CMP(low_price(l), ==, 0);

    const char * symbol = "GOOGL";
    CHECK_CMP(stock_high_price(l, symbol), == , 0);
    CHECK_CMP(stock_low_price(l, symbol), == , 0);
    CHECK_CMP(stock_avg_price(l, symbol), == , 0);

    delete_log(l);
    TEST_PASSED;
}

TEST(window_up_down) {
    trades_log * l = new_log();
    set_time_window(l,100);
    set_time_window(l,40);
    set_time_window(l,60);
    delete_log(l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
