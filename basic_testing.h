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

#define TEST_FAILED do {			\
	if (bt_fork_tests)			\
	    return BT_FAILURE;			\
	else					\
	    abort();				\
    } while(0)

#define TEST_PASSED do { return (BT_SUCCESS); } while(0)

#ifdef __cplusplus
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

static size_t bt_malloc_failure_count = 0;
static size_t bt_malloc_failure_size = 0;

static int bt_malloc_budget_enabled = 0;
static size_t bt_malloc_budget = 0;
static size_t bt_malloc_budget_curr = 0;

static int bt_budget_bytes_enabled = 0;
static size_t bt_mem_bytes_budget = 0;
static size_t bt_mem_bytes_budget_curr = 0;


BT_POSSIBLY_UNUSED
static void bt_malloc_schedule_failure (size_t count, size_t size) {
    bt_malloc_failure_count = count;
    bt_malloc_failure_size = size;
}

BT_POSSIBLY_UNUSED
static void bt_malloc_cancel_failure () {
    bt_malloc_failure_count = 0;
    bt_malloc_failure_size = 0;
}

#define BT_FAIL_MEM_ALLOCATIONS do {		\
	bt_malloc_budget_enabled = 1;		\
	bt_malloc_budget = 0;		\
	bt_malloc_budget_curr = 0;		\
    } while(0)

#define BT_SET_MEM_ALLOCATION_BUDGET(BUDGET) do {	\
	bt_malloc_budget_enabled = 1;			\
	bt_malloc_budget = (BUDGET);		\
	bt_malloc_budget_curr = (BUDGET);		\
    } while(0)

#define BT_SET_MEM_BYTES_BUDGET(BUDGET) do {		\
	bt_budget_bytes_enabled = 1;			\
	bt_mem_bytes_budget = (BUDGET);			\
	bt_mem_bytes_budget_curr = (BUDGET);		\
    } while(0)

#define BT_RESET_MEM_ALLOCATOR  do {			\
	bt_budget_bytes_enabled = 0;			\
	bt_malloc_budget_enabled = 0;			\
	bt_malloc_cancel_failure ();			\
    } while(0)


#ifdef __cplusplus
extern "C" {
#endif

extern void * __real_malloc(size_t);
extern void __real_free(void *);
extern void * __real_realloc(void *, size_t);

#ifdef __cplusplus
}
#endif

struct bt_hash_node {
    void * address;
    size_t size;
    int deleted;
};

BT_POSSIBLY_UNUSED
static struct bt_hash_node * bt_memory_table = NULL;
static size_t bt_memory_table_size = 0;
static size_t bt_memory_table_capacity = 0;

BT_POSSIBLY_UNUSED
static void bt_memory_table_free (void) {
    if (bt_memory_table) __real_free (bt_memory_table);
    bt_memory_table = NULL;
    bt_memory_table_size = 0;
    bt_memory_table_capacity = 0;
}


BT_POSSIBLY_UNUSED
static struct bt_hash_node * bt_memory_table_find (void * address) {
    if (bt_memory_table == NULL) return NULL;

    uintptr_t h = (uintptr_t) address;
    h /= alignof(max_align_t);
    h %= bt_memory_table_capacity;
    h |= 1;
    uintptr_t g = h;

    struct bt_hash_node * node = bt_memory_table + h;
    while ((node->address != address && node->address != NULL) || (node->address == NULL && node->deleted)) {
	h = (h + g)%bt_memory_table_capacity;
	node = bt_memory_table + h;
    }
    if (node->address != address) return NULL;

    return node;
}

BT_POSSIBLY_UNUSED
static struct bt_hash_node * bt_memory_table_find_or_insert (void * address) {
    if (bt_memory_table == NULL) return NULL;

    uintptr_t h = (uintptr_t) address;
    h /= alignof(max_align_t);
    h %= bt_memory_table_capacity;
    h |= 1;
    uintptr_t g = h;

    struct bt_hash_node * node = bt_memory_table + h;
    while (node->address != address && node->address != NULL) {
	h = (h + g)%bt_memory_table_capacity;
	node = bt_memory_table + h;
    }

    return node;
}


BT_POSSIBLY_UNUSED
static int bt_memory_table_set (void *address, size_t size) {
    struct bt_hash_node * node = bt_memory_table_find_or_insert (address);

    if (node && node->address != NULL) {
	node->size = size;
	return 1;
    }

    if (bt_memory_table_size*2 == bt_memory_table_capacity) {
	size_t new_cap = bt_memory_table_capacity ? 2*bt_memory_table_capacity : 128;

	struct bt_hash_node * new_table =
	    (struct bt_hash_node *) __real_malloc(new_cap*sizeof(struct bt_hash_node));
	if (!new_table) return 0;

	memset(new_table, 0, new_cap*sizeof(struct bt_hash_node));
	struct bt_hash_node * tmp = bt_memory_table;
	size_t old_cap = bt_memory_table_capacity;

	bt_memory_table = new_table;
	bt_memory_table_capacity = new_cap;
	bt_memory_table_size = 0;

	for (size_t i = 0; i < old_cap; ++i)
	    if (tmp[i].address)
		bt_memory_table_set (tmp[i].address, tmp[i].size);

	if (tmp) __real_free(tmp);
	node = bt_memory_table_find_or_insert (address);
    }

    node->address = address;
    node->size = size;
    node->deleted = 0;
    ++bt_memory_table_size;

    return 1;
}

BT_POSSIBLY_UNUSED
static int bt_memory_table_remove (void * address) {
    struct bt_hash_node * node = bt_memory_table_find (address);
    if (!node) return 0;

    node->address = NULL;
    node->deleted = 1;
    --bt_memory_table_size;

    if (bt_memory_table_capacity > 128 && bt_memory_table_size*8 < bt_memory_table_capacity) {
	size_t new_cap = bt_memory_table_capacity / 8;

	struct bt_hash_node * new_table =
	    (struct bt_hash_node *) __real_malloc(new_cap*sizeof(struct bt_hash_node));
	if (!new_table) return 0;

	memset(new_table, 0, new_cap*sizeof(struct bt_hash_node));
	struct bt_hash_node * tmp = bt_memory_table;
	size_t old_cap = bt_memory_table_capacity;

	bt_memory_table = new_table;
	bt_memory_table_capacity = new_cap;
	bt_memory_table_size = 0;

	for (size_t i = 0; i < old_cap; ++i)
	    if (tmp[i].address)
		bt_memory_table_set (tmp[i].address, tmp[i].size);

	__real_free(tmp);
    }

    return 1;
}

BT_POSSIBLY_UNUSED
static size_t bt_leaked_bytes(void) {
    size_t size = 0;

    for (size_t i = 0; i < bt_memory_table_capacity; ++i)
	if (bt_memory_table[i].address)
	    size += bt_memory_table[i].size;

    return size;
}


#ifdef __cplusplus
extern "C" {
#endif
    
BT_POSSIBLY_UNUSED
void *__wrap_malloc(size_t size) {
    if (size == 0) {
	puts("\nmalloc with size 0 is not portable");
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    }
    if (bt_malloc_failure_count > 0) {
	if (--bt_malloc_failure_count == 0) {
	    bt_malloc_failure_size = 0;
	    return 0;
	}
    }
    if (bt_malloc_failure_size > 0) {
	if (size < bt_malloc_failure_size) {
	    bt_malloc_failure_size -= size;
	} else {
	    bt_malloc_failure_count = 0;
	    bt_malloc_failure_size = 0;
	    return 0;
	}
    }
    if (bt_malloc_budget_enabled && bt_malloc_budget_curr == 0)
	return NULL;
    else if (bt_budget_bytes_enabled && bt_mem_bytes_budget_curr < size)
	return NULL;

    void * ret = __real_malloc(size);
    if (!ret) return NULL;

    if (bt_malloc_budget_enabled)
	--bt_malloc_budget_curr;
    else if (bt_budget_bytes_enabled)
	bt_mem_bytes_budget_curr -= size;

    if (!bt_memory_table_set(ret, size))
	abort();

    return ret;
}

BT_POSSIBLY_UNUSED
void __wrap_free(void * ptr) {
    const struct bt_hash_node *p = bt_memory_table_find(ptr);
    if (!p) {
	puts("\nmemory was not allocated via malloc, or possible double free");
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    }

    if (bt_malloc_budget_enabled && ++bt_malloc_budget_curr > bt_malloc_budget)
	bt_malloc_budget_curr = bt_malloc_budget;
    else if (bt_budget_bytes_enabled) {
	bt_mem_bytes_budget_curr += p->size;
	if (bt_mem_bytes_budget_curr > bt_mem_bytes_budget)
	    bt_mem_bytes_budget_curr = bt_mem_bytes_budget;
    }

    bt_memory_table_remove(ptr);
    __real_free(ptr);
}

BT_POSSIBLY_UNUSED
void *__wrap_realloc(void * ptr, size_t new_size) {
    if (new_size == 0) {
	puts("\nrealloc with size 0 is not portable");
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    }
    if (!ptr) return __wrap_malloc(new_size);

    if (bt_malloc_failure_count > 0) {
	if (--bt_malloc_failure_count == 0) {
	    bt_malloc_failure_size = 0;
	    return 0;
	}
    }
    if (bt_malloc_failure_size > 0) {
	if (new_size < bt_malloc_failure_size) {
	    bt_malloc_failure_size -= new_size;
	} else {
	    bt_malloc_failure_count = 0;
	    bt_malloc_failure_size = 0;
	    return 0;
	}
    }

    if (bt_malloc_budget_enabled && bt_malloc_budget_curr == 0)
	return NULL;

    const struct bt_hash_node * node = bt_memory_table_find(ptr);
    if (!node) {
	puts("\nrealloc of not heap allocated memory");
	if (bt_fork_tests) exit(BT_FAILURE);
	else abort();
    } else if (bt_budget_bytes_enabled && bt_mem_bytes_budget_curr + node->size < new_size)
	return NULL;

    void * ret = __real_realloc(ptr, new_size);
    if (!ret) return NULL;

    if (bt_malloc_budget_enabled)
	--bt_malloc_budget_curr;
    else if (bt_budget_bytes_enabled) {
	bt_mem_bytes_budget_curr += node->size;
	bt_mem_bytes_budget_curr -= new_size;
    }

    if (!bt_memory_table_set(ret, new_size))
	abort();

    if (ret != ptr)
	bt_memory_table_remove(ptr);

    return ret;
}

#ifdef __cplusplus
}
#endif


struct bt_test_descriptor {
    const char * name;
    int (*test_function)();
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
#define TEST(test_name)							\
BT_POSSIBLY_UNUSED static int test_name ## _test ();					\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor test_name ## _descr		\
    = { # test_name, test_name ## _test, __FILE__, __LINE__, 0};		\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor * test_name = & test_name ## _descr; \
BT_POSSIBLY_UNUSED static const int test_name ## _init = bt_add_test(test_name);	\
BT_POSSIBLY_UNUSED static int test_name ## _test ()
#else
#define  TEST(test_name)						\
BT_POSSIBLY_UNUSED static int test_name ## _test ();					\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor test_name ## _descr		\
    = { # test_name, test_name ## _test, __FILE__, __LINE__, 0};		\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor * test_name = & test_name ## _descr; \
BT_POSSIBLY_UNUSED static int test_name ## _test ()
#endif

BT_POSSIBLY_UNUSED static unsigned int bt_fail_count = 0;
BT_POSSIBLY_UNUSED static unsigned int bt_pass_count = 0;

BT_POSSIBLY_UNUSED
static int bt_run_test(const struct bt_test_descriptor * t) {
    if (RUNNING_ON_VALGRIND || !bt_fork_tests) {
	int result = t->test_function();
	if (result == BT_FAILURE) return result;

	size_t leak = bt_leaked_bytes();

	if (leak != 0) {
	    printf("\nLeaked %zu bytes in %s\n", leak, t->name);
	    BT_RESET_MEM_ALLOCATOR;
	    bt_memory_table_free();
	    TEST_FAILED;
	}

	BT_RESET_MEM_ALLOCATOR;
	bt_memory_table_free();
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
	int result = t->test_function();
	if (result == BT_FAILURE) exit(result);

	size_t leak = bt_leaked_bytes();

	if (leak != 0) {
	    printf("\nLeaked %zu bytes in %s\n", leak, t->name);
	    result = BT_FAILURE;
	}
	bt_memory_table_free();
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
	    printf("Summary: %u/%u test passed\n",			\
		   bt_pass_count, bt_pass_count + bt_fail_count);	\
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
