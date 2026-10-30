#include "basic_testing.h"

#include "../wcmp.h"

TEST(both_null_equal1) {
    CHECK_CMP(wcmp(",", ","),==,0);
}

TEST(both_null_equal2) {
    CHECK_CMP(wcmp("!@#$%^&*()-", "!@#$%^&*()-"),==,0);
}

TEST(both_null_diff1) {
    CHECK_CMP(wcmp("1234567890", "0987654321"),==,0);
}

TEST(both_null_diff2) {
    CHECK_CMP(wcmp("1234567890!@#$%^&*()-", "1234567890-+=!@#$%^&*()"),==,0);
}

TEST(both_null_diff3) {
    CHECK_CMP(wcmp("", ","),==,0);
}

TEST(both_null_diff4) {
    CHECK_CMP(wcmp(",", ""),==,0);
}

TEST(b_empty1) {
    CHECK_CMP(wcmp("123x", ""),==,1);
}

TEST(b_empty2) {
    CHECK_CMP(wcmp("--ciao++", ""),==,1);
}

TEST(equals1) {
    CHECK_CMP(wcmp("123mamma", "321mamma"),==,0);
}

TEST(equals2) {
    CHECK_CMP(wcmp(" ciao", "ciao"),==,0);
}

TEST(equals3) {
    CHECK_CMP(wcmp("*()&!@,,,ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao",
		   "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao,,,"),==,0);
}

TEST(less_than1) {
    CHECK_CMP(wcmp("432ciao", "123mamma"),==,-1);
}

TEST(less_than2) {
    CHECK_CMP(wcmp("    ciao ", "@*#&!(@$^#*ciaomamma"),==,-1);
}

TEST(less_than3) {
    CHECK_CMP(wcmp("ciaomamma", "ciaopapa"),==,-1);
}

TEST(less_than4) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaocia",
		   "!ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao"),==,-1);
}

TEST(greater_than1) {
    CHECK_CMP(wcmp("098mamma", "123ciao"),==,1);
}

TEST(greater_than2) {
    CHECK_CMP(wcmp(" ciaomamma", "   ciao"),==,1);
}

TEST(greater_than3) {
    CHECK_CMP(wcmp("ciaopapa  999", "  9 ciaomamma 8"),==,1);
}

TEST(greater_than4) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao((", "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaocia))"),==,1);
}

MAIN_TEST_DRIVER();
