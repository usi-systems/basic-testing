#include "basic_testing.h"

TEST(test_no_doc) {
    TEST_FAILED;
}

TEST(test_doc, .description="Test description") {
    TEST_FAILED;
}

TEST(check_doc) {
    CHECK(0 == 1, .desc="This assertion should fail");
    TEST_FAILED;
}

TEST(check_str_cmp_doc) {
    CHECK_STRING_CMP("str1", ==, "str2", .desc="This string comparison should fail");
    TEST_FAILED;
}

TEST(check_cmp_int_doc) {
    int a = 0;
    CHECK_CMP(a, !=, a, .desc="This integer comparison should fail");
    TEST_FAILED;
}

TEST(check_cmp_uint_doc) {
    unsigned int a = 0;
    CHECK_CMP(a, !=, a, .desc="This uint assertion should fail");
    TEST_FAILED;
}

TEST(check_cmp_double_doc) {
    double a = 0.0;
    CHECK_CMP(a, !=, a, .desc="This double assertion should fail");
    TEST_FAILED;
}

MAIN_TEST_DRIVER(test_no_doc, test_doc, check_doc, check_str_cmp_doc,
check_cmp_int_doc, check_cmp_uint_doc, check_cmp_double_doc
)
