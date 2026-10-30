#include "basic_testing.h"

#include "../wcmp.h"

TEST(both_empty) {
    CHECK_CMP(wcmp("", ""),==,0);
}

TEST(b_empty1) {
    CHECK_CMP(wcmp("x", ""),==,1);
}

TEST(b_empty2) {
    CHECK_CMP(wcmp("ciao", ""),==,1);
}

TEST(a_empty1) {
    CHECK_CMP(wcmp("", "y"),==,-1);
}

TEST(a_empty2) {
    CHECK_CMP(wcmp("", "mamma"),==,-1);
}

TEST(equals1) {
    CHECK_CMP(wcmp("mamma", "mamma"),==,0);
}

TEST(equals2) {
    CHECK_CMP(wcmp("ciao", "ciao"),==,0);
}

TEST(equals3) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao",
		   "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao"),==,0);
}

TEST(equals4) {
    CHECK_CMP(wcmp("mamma", "mamma   "),==,0);
}

TEST(equals5) {
    CHECK_CMP(wcmp("mamma   ", "mamma"),==,0);
}

TEST(less_than1) {
    CHECK_CMP(wcmp("ciao", "mamma"),==,-1);
}

TEST(less_than2) {
    CHECK_CMP(wcmp("ciao", "ciaomamma"),==,-1);
}

TEST(less_than3) {
    CHECK_CMP(wcmp("ciaomamma", "ciaopapa"),==,-1);
}

TEST(less_than4) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaocia",
		   "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao"),==,-1);
}

TEST(greater_than1) {
    CHECK_CMP(wcmp("mamma", "ciao"),==,1);
}

TEST(greater_than2) {
    CHECK_CMP(wcmp("ciaomamma", "ciao"),==,1);
}

TEST(greater_than3) {
    CHECK_CMP(wcmp("ciaopapa", "ciaomamma"),==,1);
}

TEST(greater_than4) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao", "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaocia"),==,1);
}

TEST(greater_than5) {
    CHECK_CMP(wcmp("ciaomamma", "ciao~~~"),==,1);
}

TEST(less_than5) {
    CHECK_CMP(wcmp("ciao~~~", "ciaomamma"),==,-1);
}

MAIN_TEST_DRIVER()

