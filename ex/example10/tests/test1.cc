#include "basic_testing.h"

extern "C" {
#include "../alloc.h"
}

TEST(compile) {
    TEST_PASSED;
}

TEST(fail_all_malloc) {
    ALLOC_FAIL_ALL;
    struct foo *ptr = alloc_foo();
    CHECK(ptr == NULL);

    struct foo *ptr2 = alloc_foo();
    CHECK(ptr2 == NULL);

    TEST_PASSED;
}

TEST(fail_first_malloc) {
    ALLOC_FAIL_ALL;
    struct foo *ptr = alloc_foo();
    CHECK(ptr == NULL);

    ALLOC_NO_FAIL;
    struct foo *ptr2 = alloc_foo();
    CHECK(ptr2 != NULL);

    dealloc_foo(ptr2);
    TEST_PASSED;
}

TEST(fail_all_realloc) {
    struct foo *ptr0 = alloc_foo();

    ALLOC_FAIL_ALL;
    struct foo *ptr1 = realloc_foo(ptr0);
    CHECK(ptr1 == NULL);

    struct foo *ptr2 = alloc_foo();
    struct foo *ptr3 = realloc_foo(ptr2);
    CHECK(ptr3 == NULL);
    
    TEST_PASSED;
}

TEST(fail_first_realloc) {
    struct foo *ptr0 = alloc_foo();

    ALLOC_FAIL_ALL;
    struct foo *ptr1 = realloc_foo(ptr0);
    CHECK(ptr1 == NULL);

    ALLOC_NO_FAIL;
    struct foo *ptr2 = realloc_foo(ptr0);
    CHECK(ptr2 != NULL);

    dealloc_foo(ptr2);

    TEST_PASSED;
}

MAIN_TEST_DRIVER(compile, 
    fail_all_malloc, fail_first_malloc,
    fail_all_realloc, fail_first_realloc
    );
