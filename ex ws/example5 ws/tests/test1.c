#include "basic_testing.h"

extern int stringequal(char * s1, char * s2);

TEST(two_empty) {
    char empty1[] = { 0 };
    char empty2[] = { 0 };
    CHECK(stringequal(empty1,empty2));
    TEST_PASSED;
}

TEST(first_empty) {
    CHECK(!stringequal("","a"));
    TEST_PASSED;
}

TEST(second_empty) {
    CHECK(!stringequal("a",""));
    TEST_PASSED;
}

TEST(one_char_equal) {
    char a1[] = { 'a', 0 };
    char a2[] = { 'a', 0 };
    CHECK(stringequal(a1,a2));
    TEST_PASSED;
}

TEST(same_string) {
    char s[] = { 'a', 'b', 'c', 0 };
    CHECK(stringequal(s,s));
    TEST_PASSED;
}

TEST(same_prefix1) {
    char s1[] = { 'a', 'b', 'c', 0 };
    char s2[] = { 'a', 'b', 0 };
    CHECK(!stringequal(s1,s2));
    TEST_PASSED;
}

TEST(same_prefix2) {
    char s1[] = { 'a', 'b', 'c', 0 };
    char s2[] = { 'a', 'b', 0 };
    CHECK(!stringequal(s2,s1));
    TEST_PASSED;
}

MAIN_TEST_DRIVER(two_empty,
		 first_empty,
		 second_empty,
		 one_char_equal,
		 same_string,
		 same_prefix1,
		 same_prefix2)
