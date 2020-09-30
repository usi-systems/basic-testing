#include <assert.h>
#include <string.h>
#include "basic_testing.h"

#include "../stocks.h"

TEST(adding_same_name_buf) {
    trades_log * l = new_log();

    char buf[100];
    strcpy(buf, "GOOGL");
    CHECK_CMP(new_trade(l,1.0,buf,40.0,100), ==, 1);
    strcpy(buf, "XYZ");
    CHECK_CMP(new_trade(l,2.0,buf,1000.0,200), ==, 1);
    CHECK_CMP(total_quantity(l), ==, 300);

    CHECK_CMP(stock_low_price(l,"GOOGL"), ==, 40);
    CHECK_CMP(stock_high_price(l,"GOOGL"), ==, 40);
    CHECK_CMP(stock_low_price(l,"XYZ"), ==, 1000);
    CHECK_CMP(stock_high_price(l,"XYZ"), ==, 1000);
    CHECK_CMP(stock_low_price(l,"ABC"), ==, 0);
    CHECK_CMP(stock_high_price(l,"ABC"), ==, 0);

    strcpy(buf, "ABC");
    CHECK_CMP(stock_low_price(l,buf), ==, 0);
    CHECK_CMP(stock_high_price(l,buf), ==, 0);

    strcpy(buf, "XYZ");
    CHECK_CMP(stock_low_price(l,buf), ==, 1000);
    CHECK_CMP(stock_high_price(l,buf), ==, 1000);

    delete_log(l);
    TEST_PASSED;
}

TEST(price_ranges) {
    trades_log * l = new_log();
    double t = 1;
    for (double p = 100; p <= 200; p += 5) {
	CHECK_CMP(new_trade(l,t,"GOOGL",p,10), ==, 1);
	CHECK_CMP(new_trade(l,t,"XYZ",p+100,20), ==, 1);
    }
    CHECK_CMP(stock_low_price(l,"GOOGL"), ==, 100);
    CHECK_CMP(stock_high_price(l,"GOOGL"), ==, 200);
    CHECK_CMP(stock_avg_price(l,"GOOGL"), ==, 150);

    CHECK_CMP(stock_low_price(l,"XYZ"), ==, 200);
    CHECK_CMP(stock_high_price(l,"XYZ"), ==, 300);
    CHECK_CMP(stock_avg_price(l,"XYZ"), ==, 250);

    delete_log(l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
