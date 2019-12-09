#ifndef BASIC_TESTING_H_INCLUDED
#define BASIC_TESTING_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> 

#define ck_assert_msg(expr, ...) \
    if (!(expr)) { \
	fprintf(stderr, "%s:%d: Assertion '"#expr"' failed\n" , __FILE__, __LINE__); \
	fprintf(stderr, ## __VA_ARGS__, NULL); \
	return 0; \
    }

#define ck_assert_int(X, OP, Y) do { \
  intmax_t _ck_x = (X); \
  intmax_t _ck_y = (Y); \
  if (!(_ck_x OP _ck_y)) { \
      fprintf(stderr, "%s:%d: Assertion '%s' failed: %s == %jd, %s == %jd\n", \
	      __FILE__, __LINE__, #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y); \
      return 0; \
  } \
} while (0)

#define ck_assert_uint(X, OP, Y) do { \
  uintmax_t _ck_x = (X); \
  uintmax_t _ck_y = (Y); \
  if (!(_ck_x OP _ck_y)) { \
      fprintf(stderr, "%s:%d: Assertion '%s' failed: %s == %ju, %s == %ju\n", \
	      __FILE__, __LINE__, #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y); \
      return 0; \
  } \
} while (0)

#define assert_int_eq(X, Y) ck_assert_int(X,==,Y)
#define assert_uint_eq(X, Y) ck_assert_uint(X,==,Y)

typedef struct {
    const char * name;
    int (*test_function)();
    const char * file;
    int line;
} test_descriptor;

#define TEST(_Name) \
static int _Name ## _fn (); \
static const test_descriptor _Name ## _descr = { # _Name, _Name ## _fn, __FILE__, __LINE__};	\
static const test_descriptor * _Name = & _Name ## _descr; \
static int _Name ## _fn ()

#define TEST_PASSED do { return (1); } while(0)

#define TEST_SUITE(_Name) \
unsigned int _Name ## _failed; \
unsigned int _Name ## _passed; \
const test_descriptor * _Name ## _suite []

#define RUN_SUITE(_Name)						\
    do {								\
	_Name ## _failed = 0;						\
	_Name ## _passed = 0;						\
	for (int _i = 0; _i < sizeof( _Name ## _suite )/sizeof(test_descriptor *); ++_i) { \
	    if (!(_Name ## _suite [_i]->test_function())) {		\
		_Name ## _failed += 1;					\
		fprintf(stderr, "Test suite "#_Name": test %s failed\n", _Name ## _suite [_i]->name); \
	    } else {							\
		_Name ## _passed += 1;					\
	    }								\
	}								\
} while (0) 

#define TEST_SUITE_PASS(_Name) (_Name ## _failed == 0)

#define PRINT_SUITE_RESULTS(_Name) \
    do { \
    printf("Test suite "#_Name": pass %u/%u  ", _Name ## _passed, _Name ## _passed + _Name ## _failed); \
    } while(0)

#endif
