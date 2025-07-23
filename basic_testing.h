/* Basic Testing is a simple and very basic testing framework.
 *
 * Copyright (C) 2018-2020  Antonio Carzaniga
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BASIC_TESTING_H_INCLUDED
#define BASIC_TESTING_H_INCLUDED

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#ifdef __cplusplus
#include <iostream>
#endif

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#ifdef __has_include
#if __has_include(<sys/resource.h>)
#include <sys/resource.h>
#define WITH_RUSAGE 1
#endif
#endif

#ifdef __has_include
#if __has_include(<valgrind.h>)
#include <valgrind.h>
#elif __has_include(<valgrind/valgrind.h>)
#include <valgrind/valgrind.h>
#else
#define RUNNING_ON_VALGRIND 0
#endif
#else
#define RUNNING_ON_VALGRIND 0
#endif

/* SUCCESS/FAILURE macros
 */
#define BT_FAILURE 0
#define BT_SUCCESS 1
#define BT_SKIP 2

#define TEST_FAILED do {			\
        if (bt_fork_tests) {			\
            *bt_result = BT_FAILURE;		\
	    return;				\
        } else					\
	    abort();				\
    } while(0)

#define TEST_PASSED do { *bt_result = BT_SUCCESS; return; } while(0)
#define TEST_SKIPPED do { *bt_result = BT_SKIP; return; } while(0)

#if defined(__cpp_attributes) && defined(__has_cpp_attribute) && __has_cpp_attribute(maybe_unused)
#define BT_POSSIBLY_UNUSED [[maybe_unused]]
#elif defined(__has_c_attribute) && __has_c_attribute(maybe_unused)
#define BT_POSSIBLY_UNUSED [[maybe_unused]]
#elif defined(__GNUC__) || defined(__clang__)
#define BT_POSSIBLY_UNUSED __attribute__((unused))
#endif
#ifndef BT_POSSIBLY_UNUSED
#define BT_POSSIBLY_UNUSED
#endif

/* Assertion checks
 */

/* Check for generic Boolean expressions
 */
#define CHECK(expr) do {					\
	if (!(expr)) {						\
	    printf("\n%s:%d: Assertion '"#expr"' failed\n",	\
		   __FILE__, __LINE__);				\
	    TEST_FAILED;					\
	}							\
    } while (0)

/* Check for comparison between two C strings based on binary
 * relations/operators (==, >=, <=, !=, <, >).
 */
#define CHECK_STRING_CMP(X,OP,Y) do {					\
	const char * x_ = (X);						\
	const char * y_ = (Y);						\
	if (!(strcmp(x_, y_) OP 0)) {					\
            printf("\n%s:%d: Assertion '"#X" "#OP" "#Y"' failed: %s "#OP" %s\n", \
		   __FILE__, __LINE__, x_, y_); \
	    TEST_FAILED;						\
	}								\
    } while (0)

/* Checks for comparisons based on binary relations/operators (==, >=,
 * <=, !=).  We can do this easily with a single generic check in C++.
 * In C we must have specific checks for specific types.
 */
#ifdef __cplusplus

#define CHECK_CMP(X,OP,Y) do {						\
	auto x_ = (X);							\
	decltype (x_) y_ = (Y);						\
	if (!(x_ OP y_)) {						\
	    std::cout << std::endl <<__FILE__ << ":" << __LINE__	\
		      << ": Assertion '"#X" "#OP" "#Y"' failed: "	\
                      << x_ << " "#OP" " << y_ << std::endl;		\
	    TEST_FAILED;						\
	}								\
    } while (0)

#else

enum bt_cmp_operator {
    BT_EQ, BT_NE, BT_LE, BT_GE, BT_LT, BT_GT, BT_UNKNOWN
};

static enum bt_cmp_operator bt_operator (const char * op) {
    switch (op[1]) {
    case '=':
	switch (op[0]) {
	case '=': return BT_EQ;
	case '!': return BT_NE;
	case '<': return BT_LE;
	case '>': return BT_GE;
	default: return BT_UNKNOWN;
	}
    case '<': return BT_LT;
    case '>': return BT_GT;
    default: return BT_UNKNOWN;
    }
}

BT_POSSIBLY_UNUSED
static int check_cmp_int (int x, int y, const char * op,
			  const char * x_str, const char * y_str,
			  const char * filename, int line) {
    int res;
    switch (bt_operator(op)) {
    case BT_EQ: res = (x == y); break;
    case BT_NE: res = (x != y); break;
    case BT_LE: res = (x <= y); break;
    case BT_GE: res = (x >= y); break;
    case BT_LT: res = (x < y); break;
    case BT_GT: res = (x > y); break;
    default: res = 0;
    }
    if (!res)
	printf("\n%s:%d: Assertion '%s %s %s' failed: %d %s %d\n", \
	       filename, line, x_str, op, y_str, x, op, y);
    return res;
}

BT_POSSIBLY_UNUSED
static int check_cmp_uint (unsigned int x, unsigned int y, const char * op,
			  const char * x_str, const char * y_str,
			  const char * filename, int line) {
    int res;
    switch (bt_operator(op)) {
    case BT_EQ: res = (x == y); break;
    case BT_NE: res = (x != y); break;
    case BT_LE: res = (x <= y); break;
    case BT_GE: res = (x >= y); break;
    case BT_LT: res = (x < y); break;
    case BT_GT: res = (x > y); break;
    default: res = 0;
    }
    if (!res)
	printf("\n%s:%d: Assertion '%s %s %s' failed: %u %s %u\n", \
	       filename, line, x_str, op, y_str, x, op, y);
    return res;
}

BT_POSSIBLY_UNUSED
static int check_cmp_double (double x, double y, const char * op,
			     const char * x_str, const char * y_str,
			     const char * filename, int line) {
    int res;
    switch (bt_operator(op)) {
    case BT_EQ: res = (x == y); break;
    case BT_NE: res = (x != y); break;
    case BT_LE: res = (x <= y); break;
    case BT_GE: res = (x >= y); break;
    case BT_LT: res = (x < y); break;
    case BT_GT: res = (x > y); break;
    default: res = 0;
    }
    if (!res)
	printf("\n%s:%d: Assertion '%s %s %s' failed: %f %s %f\n", \
	       filename, line, x_str, op, y_str, x, op, y);
    return res;
}

BT_POSSIBLY_UNUSED
static int check_cmp_ptr (void * x, void * y, const char * op,
			     const char * x_str, const char * y_str,
			     const char * filename, int line) {
    int res;
    switch (bt_operator(op)) {
    case BT_EQ: res = (x == y); break;
    case BT_NE: res = (x != y); break;
    case BT_LE: res = (x <= y); break;
    case BT_GE: res = (x >= y); break;
    case BT_LT: res = (x < y); break;
    case BT_GT: res = (x > y); break;
    default: res = 0;
    }
    if (!res)
	printf("\n%s:%d: Assertion '%s %s %s' failed: %p %s %p\n", \
	       filename, line, x_str, op, y_str, x, op, y);
    return res;
}

#define CHECK_CMP(X,OP,Y) do {						\
    if (! _Generic ((Y),						\
                    int : check_cmp_int,				\
           unsigned int : check_cmp_uint,				\
		 double : check_cmp_double,				\
                 void * : check_cmp_ptr)				\
               ((X),(Y),#OP,#X,#Y,__FILE__,__LINE__)) {			\
        TEST_FAILED;							\
    }									\
} while (0)

#endif	/* C++/C */

#define CHECK_UINT_CMP(X,OP,Y) CHECK_CMP(X,OP,Y)

#define CHECK_INT_CMP(X,OP,Y) CHECK_CMP(X,OP,Y)

#define CHECK_DOUBLE_CMP(X,OP,Y) CHECK_CMP(X,OP,Y)

BT_POSSIBLY_UNUSED
static int bt_fork_tests = 1;

BT_POSSIBLY_UNUSED
static unsigned int bt_timeout = 3; /* three seconds */

BT_POSSIBLY_UNUSED
static int bt_verbose = 1;

static int bt_mem_checks_disabled = 0;

BT_POSSIBLY_UNUSED
static int MEM_CHECKS_DISABLED () {
    return bt_mem_checks_disabled;
}

/* bt_mem_table_failed is a Boolean flag that indicates that the
   framework has failed to keep track of memory allocations in its
   hash table, and therefore all memory checks are disabled.  More
   specifically, a mem-table failure happens when the real malloc
   succeeds in allocating user memory, but then fails in allocating
   memory to grow the memory table.
*/
static int bt_mem_table_failed = 0;

static size_t bt_mem_failure_count = 0;
static size_t bt_mem_failure_size = 0;

static int bt_mem_budget_enabled = 0;
static size_t bt_mem_budget = 0;
static size_t bt_mem_budget_curr = 0;

static int bt_mem_bytes_budget_enabled = 0;
static size_t bt_mem_bytes_budget = 0;
static size_t bt_mem_bytes_budget_curr = 0;

/* The main parameters of the BT Mem table are macros, in case we want
   to change their values through compiler options.
  */
#ifndef BT_MEM_TABLE_MIN_SIZE
#define BT_MEM_TABLE_MIN_SIZE 128
#endif
#ifndef BT_MEM_TABLE_REHASH_HIGH_RATIO
/* By default, we double the size of the table when the size of the
   table, meaning the number of elements actually stored in the table,
   is more than 1/BT_MEM_TABLE_REHASH_HIGH_RATIO of the capacity of
   the table.  So, by default, we grow the table when the occupancy is
   more than half the capacity. */
#define BT_MEM_TABLE_REHASH_HIGH_RATIO 2
#endif
#ifndef BT_MEM_TABLE_REHASH_LOW_RATIO
/* By default, we cut the size of the table in half when the size of
   the table, meaning the number of elements actually stored in the
   table, is less than 1/BT_MEM_TABLE_REHASH_LOW_RATIO of the capacity
   of the table.  So, by default, we shrink the table when the
   occupancy is less than 1/8 of the capacity.  We never shrink below
   BT_MEM_TABLE_MIN_SIZE */
#define BT_MEM_TABLE_REHASH_LOW_RATIO 8
#endif

/* Schedule a one-time failure of any memory allocation functions as
   soon as `count' invocation are made or `size' bytes are allocated
   in total and not considering deallocations.  Notice that if you
   want the next memory allocation function to fail, `count' must be
   set to 1.  Setting `count' to 0 means ignoring the number of calls.
   Similarly, setting `size' to 0 means ignoring the amount of
   allocated memory.
 */
BT_POSSIBLY_UNUSED
static void bt_mem_schedule_failure (size_t count, size_t size) {
    bt_mem_failure_count = count;
    bt_mem_failure_size = size;
}

#define MEM_SCHEDULE_FAILURE(C,S) do {		\
    if (bt_mem_checks_disabled) {		\
        TEST_SKIPPED;				\
    } else {					\
        bt_mem_schedule_failure ((C),(S));	\
    }						\
} while (0)

/* Cancel any previously scheduled one-time failure of memory
   allocation functions.
 */
BT_POSSIBLY_UNUSED
static void bt_mem_cancel_failure (void) {
    bt_mem_failure_count = 0;
    bt_mem_failure_size = 0;
}

#define MEM_CANCEL_FAILURE(X) do {	\
    if (bt_mem_checks_disabled) {	\
        TEST_SKIPPED;			\
    } else {				\
        bt_mem_cancel_failure ();	\
    }					\
} while (0)

/* Cause all memory allocation functions to fail from now on.  This
   has an immediate effect, meaning that the next allocation function
   will fail.
 */
BT_POSSIBLY_UNUSED
static void bt_mem_fail_all (void) {
    bt_mem_budget_enabled = 1;
    bt_mem_budget = 0;
    bt_mem_budget_curr = 0;
}

#define MEM_FAIL_ALL(X) do {		\
    if (bt_mem_checks_disabled) {	\
        TEST_SKIPPED;			\
    } else {				\
        bt_mem_fail_all ();		\
    }					\
} while (0)

/* Set a maximum allocation budget in terms of number of invocations
   of memory allocation functions.  As soon as this budget of calls is
   exceeded, any allocation function will fail.  A call to `free' will
   count as -1.
 */
void bt_mem_set_allocation_budget (size_t budget) {
    bt_mem_budget_enabled = 1;
    bt_mem_budget = budget;
    bt_mem_budget_curr = budget;
}

#define MEM_SET_ALLOCATION_BUDGET(B) do {	\
    if (bt_mem_checks_disabled) {		\
        TEST_SKIPPED;				\
    } else {					\
        bt_mem_set_allocation_budget (B);	\
    }						\
} while (0)

/* Set a maximum allocation budget in terms of amount of memory.  As
   soon as this budget is exceeded, any allocation function will fail.
   Calling `free(p)' will discount the amount of memory previously
   allocated with pointer `p'.
 */
void bt_mem_set_bytes_budget (size_t budget) {
    bt_mem_bytes_budget_enabled = 1;
    bt_mem_bytes_budget = budget;
    bt_mem_bytes_budget_curr = budget;
}

#define MEM_SET_BYTES_BUDGET(B) do {	\
    if (bt_mem_checks_disabled) {	\
        TEST_SKIPPED;			\
    } else {				\
        bt_mem_set_bytes_budget (B);	\
    }					\
} while (0)

/* Completely reset the instrumentation of the memory allocation
   functions.  Failures are reset, and invocations and bytes
   budgets are also canceled.
 */
void bt_mem_reset_allocator (void) {
    bt_mem_table_failed = 0;
    bt_mem_bytes_budget_enabled = 0;
    bt_mem_budget_enabled = 0;
    bt_mem_cancel_failure ();
}

#define MEM_RESET_ALLOCATOR(X) do {	\
    if (bt_mem_checks_disabled) {	\
        TEST_SKIPPED;			\
    } else {				\
        bt_mem_reset_allocator ();	\
    }					\
} while (0)

#ifdef __cplusplus
extern "C" {
#endif

extern void * __real_malloc (size_t);
extern void __real_free (void *);
extern void * __real_realloc (void *, size_t);
extern void * __real_calloc (size_t, size_t);
extern void * __real_reallocarray (void *, size_t, size_t);

#ifdef __cplusplus
}
#endif

struct bt_mem_node {
    void * address;
    size_t size;
    int deleted;
};

BT_POSSIBLY_UNUSED
static struct bt_mem_node * bt_mem_table = NULL;
static size_t bt_mem_table_size = 0;
static size_t bt_mem_table_capacity = 0;

BT_POSSIBLY_UNUSED
static void bt_mem_table_free (void) {
    if (bt_mem_table) __real_free (bt_mem_table);
    bt_mem_table = NULL;
    bt_mem_table_size = 0;
    bt_mem_table_capacity = 0;
}

static size_t bt_ptr_hash (void * address) {
    uintptr_t h = (uintptr_t) address;
    h /= alignof(max_align_t);
    h %= bt_mem_table_capacity;
    h |= 1;
    return h;
}

BT_POSSIBLY_UNUSED
static struct bt_mem_node * bt_mem_table_find (void * address) {
    if (bt_mem_table == NULL) return NULL;

    size_t h = bt_ptr_hash(address);
    size_t g = h;

    struct bt_mem_node * node = bt_mem_table + h;
    while ((node->address != address && node->address != NULL) || (node->address == NULL && node->deleted)) {
	h = (h + g)%bt_mem_table_capacity;
	node = bt_mem_table + h;
    }
    if (node->address != address) return NULL;

    return node;
}

BT_POSSIBLY_UNUSED
static struct bt_mem_node * bt_mem_table_find_or_insert (void * address) {
    if (bt_mem_table == NULL) return NULL;

    size_t h = bt_ptr_hash(address);
    size_t g = h;

    struct bt_mem_node * node = bt_mem_table + h;
    while (node->address != address && node->address != NULL) {
	h = (h + g)%bt_mem_table_capacity;
	node = bt_mem_table + h;
    }

    return node;
}

static int bt_mem_rehash (size_t new_cap) {
    struct bt_mem_node * new_table =
	(struct bt_mem_node *) __real_malloc(new_cap*sizeof(struct bt_mem_node));
    if (!new_table) return 0;

    memset(new_table, 0, new_cap*sizeof(struct bt_mem_node));
    struct bt_mem_node * tmp = bt_mem_table;
    size_t old_cap = bt_mem_table_capacity;

    bt_mem_table = new_table;
    bt_mem_table_capacity = new_cap;

    for (size_t i = 0; i < old_cap; ++i) {
	if (tmp[i].address) {
	    struct bt_mem_node * node = bt_mem_table_find_or_insert(tmp[i].address);
	    node->address = tmp[i].address;
	    node->size = tmp[i].size;
	}
    }
    if (tmp) __real_free(tmp);
    return 1;
}

BT_POSSIBLY_UNUSED
static int bt_mem_table_set (void *address, size_t size) {
    struct bt_mem_node * node = bt_mem_table_find_or_insert (address);

    if (node && node->address != NULL) {
	node->size = size;
	return 1;
    }

    if (bt_mem_table_size*BT_MEM_TABLE_REHASH_HIGH_RATIO >= bt_mem_table_capacity) {
	size_t new_cap = bt_mem_table_capacity ? 2*bt_mem_table_capacity : BT_MEM_TABLE_MIN_SIZE;
	if (!bt_mem_rehash(new_cap))
	    return 0;
	node = bt_mem_table_find_or_insert (address);
    }

    node->address = address;
    node->size = size;
    node->deleted = 0;
    ++bt_mem_table_size;

    return 1;
}

BT_POSSIBLY_UNUSED
static int bt_mem_table_remove (void * address) {
    struct bt_mem_node * node = bt_mem_table_find (address);
    if (!node) return 0;

    node->address = NULL;
    node->deleted = 1;
    --bt_mem_table_size;

    if (bt_mem_table_capacity > BT_MEM_TABLE_MIN_SIZE
	&& bt_mem_table_size*BT_MEM_TABLE_REHASH_LOW_RATIO < bt_mem_table_capacity)
	if (!bt_mem_rehash(bt_mem_table_capacity / 2))
	    return 0;

    return 1;
}

BT_POSSIBLY_UNUSED
static size_t bt_leaked_bytes (void) {
    size_t size = 0;

    for (size_t i = 0; i < bt_mem_table_capacity; ++i)
	if (bt_mem_table[i].address)
	    size += bt_mem_table[i].size;

    return size;
}


#ifdef __cplusplus
extern "C" {
#endif

BT_POSSIBLY_UNUSED
void *__wrap_malloc (size_t size) {
    if (bt_mem_checks_disabled)
	return __real_malloc(size);
    if (size == 0) {
	fputs("\nmalloc with size 0 is not portable\n", stderr);
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    }
    if (bt_mem_failure_count > 0) {
	if (--bt_mem_failure_count == 0) {
	    bt_mem_failure_size = 0;
	    return 0;
	}
    }
    if (bt_mem_failure_size > 0) {
	if (size < bt_mem_failure_size) {
	    bt_mem_failure_size -= size;
	} else {
	    bt_mem_failure_count = 0;
	    bt_mem_failure_size = 0;
	    return 0;
	}
    }
    if (bt_mem_budget_enabled && bt_mem_budget_curr == 0)
	return NULL;
    else if (bt_mem_bytes_budget_enabled && bt_mem_bytes_budget_curr < size)
	return NULL;

    void * ret = __real_malloc(size);
    if (!ret) return NULL;

    if (bt_mem_budget_enabled)
	--bt_mem_budget_curr;
    else if (bt_mem_bytes_budget_enabled)
	bt_mem_bytes_budget_curr -= size;

    if (!bt_mem_table_set(ret, size)) {
	bt_mem_table_failed = 1;
    }
    return ret;
}

BT_POSSIBLY_UNUSED
void __wrap_free (void * ptr) {
    if (bt_mem_checks_disabled) {
	__real_free(ptr);
	return;
    }
    const struct bt_mem_node *p = bt_mem_table_find(ptr);
    if (!p) {
	fputs("\nmemory was not allocated via malloc, or possible double free\n", stderr);
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    }

    if (bt_mem_budget_enabled && ++bt_mem_budget_curr > bt_mem_budget)
	bt_mem_budget_curr = bt_mem_budget;
    else if (bt_mem_bytes_budget_enabled) {
	bt_mem_bytes_budget_curr += p->size;
	if (bt_mem_bytes_budget_curr > bt_mem_bytes_budget)
	    bt_mem_bytes_budget_curr = bt_mem_bytes_budget;
    }
    bt_mem_table_remove(ptr);
    __real_free(ptr);
}

BT_POSSIBLY_UNUSED
void *__wrap_realloc (void * ptr, size_t new_size) {
    if (bt_mem_checks_disabled)
	return __real_realloc (ptr, new_size);

    if (new_size == 0) {
	fputs("\nrealloc with size 0 is not portable\n", stderr);
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    }
    if (!ptr) return __wrap_malloc(new_size);

    if (bt_mem_failure_count > 0) {
	if (--bt_mem_failure_count == 0) {
	    bt_mem_failure_size = 0;
	    return 0;
	}
    }
    if (bt_mem_failure_size > 0) {
	if (new_size < bt_mem_failure_size) {
	    bt_mem_failure_size -= new_size;
	} else {
	    bt_mem_failure_count = 0;
	    bt_mem_failure_size = 0;
	    return 0;
	}
    }

    if (bt_mem_budget_enabled && bt_mem_budget_curr == 0)
	return NULL;

    const struct bt_mem_node * node = bt_mem_table_find(ptr);
    if (!node) {
	fputs("\nrealloc of not heap allocated memory\n", stderr);
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    } else if (bt_mem_bytes_budget_enabled && bt_mem_bytes_budget_curr + node->size < new_size)
	return NULL;

    void * ret = __real_realloc(ptr, new_size);
    if (!ret) return NULL;

    if (bt_mem_budget_enabled)
	--bt_mem_budget_curr;
    else if (bt_mem_bytes_budget_enabled) {
	bt_mem_bytes_budget_curr += node->size;
	bt_mem_bytes_budget_curr -= new_size;
    }

    if (!bt_mem_table_set(ret, new_size)) {
	bt_mem_table_failed = 1;
    }

    if (ret != ptr)
	bt_mem_table_remove(ptr);

    return ret;
}

void * __wrap_calloc (size_t nmemb, size_t size) {
    if (bt_mem_checks_disabled)
	return __real_calloc(nmemb, size);

    if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb <= size)
	return NULL;
    size_t len = nmemb * size;
    void * p = __wrap_malloc (len);
    if (p) memset(p, 0, len);
    return p;
}

void * __wrap_reallocarray (void * ptr, size_t nmemb, size_t size) {
    if (bt_mem_checks_disabled)
	return __real_reallocarray(ptr, nmemb, size);

    if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb <= size)
	return NULL;
    size_t len = nmemb * size;
    return __wrap_realloc (ptr, len);
}

#ifdef __cplusplus
}
#endif


struct bt_test_descriptor {
    const char * name;
    void (*test_function)(int * result);
    const char * file;
    int line;
    struct bt_test_descriptor * next;
};

static struct bt_test_descriptor * bt_main_test_suite = 0;
static struct bt_test_descriptor ** bt_last_test_p = &bt_main_test_suite;

BT_POSSIBLY_UNUSED
static int bt_add_test(struct bt_test_descriptor * t) {
    t->next = 0;
    *bt_last_test_p = t;
    bt_last_test_p = &(t->next);
    return 1;
}

#ifdef __cplusplus
#define TEST(test_name)									\
BT_POSSIBLY_UNUSED static void test_name ## _test (int * bt_result);			\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor test_name ## _descr		\
    = { # test_name, test_name ## _test, __FILE__, __LINE__, 0};		\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor * test_name = & test_name ## _descr; \
BT_POSSIBLY_UNUSED static const int test_name ## _init = bt_add_test(test_name);	\
BT_POSSIBLY_UNUSED static void test_name ## _test (int * bt_result)
#else
#define  TEST(test_name)						\
BT_POSSIBLY_UNUSED static void test_name ## _test (int * bt_result);			\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor test_name ## _descr		\
    = { # test_name, test_name ## _test, __FILE__, __LINE__, 0};		\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor * test_name = & test_name ## _descr; \
BT_POSSIBLY_UNUSED static void test_name ## _test (int * bt_result)
#endif

BT_POSSIBLY_UNUSED static unsigned int bt_fail_count = 0;
BT_POSSIBLY_UNUSED static unsigned int bt_pass_count = 0;
BT_POSSIBLY_UNUSED static unsigned int bt_skip_count = 0;

BT_POSSIBLY_UNUSED
static int bt_run_test(const struct bt_test_descriptor * t) {
    if (RUNNING_ON_VALGRIND || !bt_fork_tests) {
        int result = BT_SUCCESS;
        t->test_function(&result);
	if (result == BT_FAILURE) 
	    return result;
	if (bt_mem_table_failed) {
	    printf("\nWARNING: Leakage test is disabled in %s\n", t->name);
	    result = BT_FAILURE;
	} else {
	    size_t leak = bt_leaked_bytes();
	    if (leak != 0) {
		printf("\nLeaked %zu bytes in %s\n", leak, t->name);
		result = BT_FAILURE;
	    }
	}
	bt_mem_reset_allocator();
	bt_mem_table_free();
	return result;
    }
    pid_t pid;
    /* Make sure the child starts with empty I/O buffers. */
    fflush(stdout);
    fflush(stderr);
#ifdef WITH_RUSAGE
    struct rusage usage_before;
    struct rusage usage_after;
    getrusage(RUSAGE_CHILDREN, &usage_before);
#endif
    pid = fork();

    if (pid == (pid_t)-1) {
	printf("Cannot fork test %s. %s [%d]\n", t->name, strerror(errno), errno);
	return BT_FAILURE;
    } else if (pid == 0) {
	/* Child: Do the test. */
	if (bt_timeout > 0)
	    alarm(bt_timeout);
	int result = BT_SUCCESS;
	t->test_function(&result);
	if (result == BT_FAILURE)
	    exit(result);
	if (bt_mem_table_failed) {
	    printf("\nWARNING: Leakage test is disabled in %s\n", t->name);
	    result = BT_FAILURE;
	} else {
	    size_t leak = bt_leaked_bytes();
	    if (leak != 0) {
		printf("\nLeaked %zu bytes in %s\n", leak, t->name);
		result = BT_FAILURE;
	    }
	}
	bt_mem_table_free();
	exit(result);
    } else {
	/* Parent: Wait until child terminates and analyze its exit code. */
	int exit_code;
	waitpid(pid, &exit_code, 0);
#ifdef WITH_RUSAGE
	getrusage(RUSAGE_CHILDREN, &usage_after);
#endif
	if (WIFEXITED(exit_code)) {
	    switch (WEXITSTATUS(exit_code)) {
	    case BT_SUCCESS: return BT_SUCCESS;
	    case BT_FAILURE: break;
	    default:  printf("Unexpected exit code [%d]", WEXITSTATUS(exit_code));
	    }
	} else if (WIFSIGNALED(exit_code)) {
	    const char* signame;
	    int sig = WTERMSIG(exit_code);
	    switch (sig) {
	    case SIGINT:  signame = "SIGINT"; break;
	    case SIGHUP:  signame = "SIGHUP"; break;
	    case SIGQUIT: signame = "SIGQUIT"; break;
	    case SIGABRT: signame = "SIGABRT"; break;
	    case SIGKILL: signame = "SIGKILL"; break;
	    case SIGSEGV: signame = "SIGSEGV"; break;
	    case SIGILL:  signame = "SIGILL"; break;
	    case SIGTERM: signame = "SIGTERM"; break;
	    case SIGALRM:
#ifdef WITH_RUSAGE
		if (usage_after.ru_utime.tv_sec - usage_before.ru_utime.tv_sec >= bt_timeout - 1)
		    signame = "SIGALARM (timeout), infinite loop?";
		else
		    signame = "SIGALARM (timeout), stuck on input?";
#else
		signame = "SIGALARM (timeout)";
#endif
		break;
	    default: signame = 0;
	    }
	    if (bt_verbose) {
		if (signame)
		    printf("interrupted by %s\n", signame);
		else
		    printf("interrupted by signal %d\n", sig);
	    }
	} else {
	    if (bt_verbose)
		printf("Test ended in an unexpected way [%d]\n", exit_code);
	}
	return BT_FAILURE;
    }
}

BT_POSSIBLY_UNUSED
static void bt_run_and_record_test(const struct bt_test_descriptor * t) {
    if (bt_verbose)
	printf("test %-40s  ", t->name);
    switch (bt_run_test(t)) {
    case BT_FAILURE:
	bt_fail_count += 1;
	if (bt_verbose)
	    printf("test %-40s  FAIL\n", t->name);
	break;
    case BT_SKIP:
	bt_skip_count += 1;
	if (bt_verbose)
	    printf("SKIP\n");
	break;
    case BT_SUCCESS:
	bt_pass_count += 1;
	if (bt_verbose)
	    printf("PASS\n");
	break;
    }
}

#define RUN_TEST(name) do { bt_run_and_record_test(name); } while (0);

#define RUN_TESTS(...) do {						\
	struct bt_test_descriptor * T_[] = { __VA_ARGS__, 0 };		\
	for (struct bt_test_descriptor ** ti = T_; *ti != 0; ++ti) {	\
	    bt_run_and_record_test(*ti);				\
	}								\
    } while (0)

#define PRINT_TEST_RESULTS						\
    do {								\
	if (bt_verbose)							\
	printf("Summary: %u/%u test passed, %u skipped\n",		\
        bt_pass_count, bt_pass_count + bt_fail_count, bt_skip_count);	\
    } while (0)

#define ALL_TESTS_PASSED (bt_fail_count == 0)

#define EXIT_ALL_TESTS_PASSED ((bt_fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE)

BT_POSSIBLY_UNUSED
const char * bt_test_usage
  = "usage: %s [-d] [-v] [-n] [-t <seconds>]  [-- <test_name> ...]\n"
    "\t-d            :: run tests in debug mode (no fork, no timeout)\n"
    "\t-q            :: quiet: minimal output\n"
    "\t-n            :: simple output without a new-line\n"
    "\t-t <seconds>  :: set timeout for each test (default 3s)\n"
    "\t-m            :: disable memory checks\n"
    "\t-- <names>... :: run the specified tests only\n"
    ;

BT_POSSIBLY_UNUSED
int bt_test_names_argc = -1;

BT_POSSIBLY_UNUSED
void bt_parse_args(int argc, char * argv []) {
    for (int i = 1; i < argc; ++i) {
	if (strcmp(argv[i], "-d")==0) {
	    bt_fork_tests = 0;
	} else if (strcmp(argv[i], "-q")==0) {
	    bt_verbose = 0;
	} else if (strcmp(argv[i], "-v")==0) {
	    bt_verbose = 1;
	} else if (strcmp(argv[i], "-t")==0 && i + 1 < argc) {
	    i += 1;
	    bt_timeout = atoi(argv[i]);
	} else if (strcmp(argv[i], "-m")==0) {
	    bt_mem_checks_disabled = 1;
	} else if (strcmp(argv[i], "--")==0) {
	    bt_test_names_argc = i + 1;
	    return;
	} else {
	    printf(bt_test_usage, argv[0]);
	    exit(EXIT_FAILURE);
	}
    }
}

#define INIT_TESTING(argc,argv) bt_parse_args(argc,argv)

int bt_test_driver(int argc, char * argv[]) {
    bt_parse_args(argc, argv);
    if (bt_test_names_argc == -1) {
	for (struct bt_test_descriptor * t = bt_main_test_suite; t != 0; t = t->next)
	    bt_run_and_record_test(t);
    } else {
	for (int i = bt_test_names_argc; i < argc; ++i)
	    for (struct bt_test_descriptor * t = bt_main_test_suite; t != 0; t = t->next)
		if (strcmp(argv[i], t->name) == 0)
		    bt_run_and_record_test(t);
    }
    PRINT_TEST_RESULTS;
    return EXIT_ALL_TESTS_PASSED;
}

#ifdef __cplusplus
#define MAIN_TEST_DRIVER(...)						\
    int main(int argc, char * argv[]) {					\
	return bt_test_driver(argc, argv);				\
    }
#else
#define MAIN_TEST_DRIVER(...)						\
    int main(int argc, char * argv[]) {					\
	struct bt_test_descriptor * suite [] = { __VA_ARGS__ };		\
	const unsigned n = sizeof(suite)/sizeof(struct bt_test_descriptor *); \
	for (unsigned i = 0; i < n; ++i)				\
	    bt_add_test(suite[i]);					\
	return bt_test_driver(argc, argv);				\
    }
#endif

#endif /* BASIC_TESTING_H_INCLUDED */
