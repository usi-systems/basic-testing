#include "basic_testing.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>



static int int_comparator (const void * a, const void * b) {
    const int aval = (*(const int *)a);
    const int bval = (*(const int *)b);
    return aval - bval;
}


TEST (compile) {
    TEST_PASSED;
}


// ctype.h functions
TEST (ctype_no_leaks) {
    CHECK (isalnum ('a'));
    CHECK (isalpha ('a'));
    CHECK (iscntrl ('\n'));
    CHECK (isdigit ('1'));
    CHECK (isgraph ('a'));
    CHECK (islower ('a'));
    CHECK (isprint ('a'));
    CHECK (ispunct ('.'));
    CHECK (isspace (' '));
    CHECK (isupper ('A'));
    CHECK (isxdigit ('A'));
    CHECK_CMP (toupper ('a'),==,'A');
    CHECK_CMP (tolower ('A'),==,'a');
    TEST_PASSED;
}


// string.h functions
TEST (strcpy_no_leaks) {
    char out[10];
    strcpy (out, "hello");
    CHECK_STRING_CMP (out,==,"hello");
    TEST_PASSED;
}


TEST (strncpy_no_leaks) {
    char out[10];
    strncpy (out, "hello", 6);
    CHECK_STRING_CMP (out,==,"hello");
    TEST_PASSED;
}


TEST (strcat_no_leaks) {
    char out[10] = "hello";
    strcat (out, "he");
    CHECK_STRING_CMP (out,==,"hellohe");
    TEST_PASSED;
}


TEST (strncat_no_leaks) {
    char out[10] = "hello";
    strncat (out, "he", 3);
    CHECK_STRING_CMP (out,==,"hellohe");
    TEST_PASSED;
}


TEST (strcmp_no_leaks) {
    CHECK_CMP (strcmp ("hello", "hello"),==,0);
    TEST_PASSED;
}


TEST (strncmp_no_leaks) {
    CHECK_CMP (strncmp ("hello", "hello2", 3),==,0);
    TEST_PASSED;
}


TEST (strchr_no_leaks) {
    const char *s = "hello";
    CHECK_STRING_CMP (strchr (s, 'l'),==,"llo");
    TEST_PASSED;
}


TEST (strrchr_no_leaks) {
    const char *s = "hello";
    CHECK_STRING_CMP (strrchr (s, 'l'),==,"lo");
    TEST_PASSED;
}


TEST (strspn_no_leaks) {
    const char *s = "hello";
    CHECK_CMP (strspn (s, "hel"),==,4);
    TEST_PASSED;
}


TEST (strcspn_no_leaks) {
    const char *s = "hello";
    CHECK_CMP (strcspn (s, "h"),==,0);
    TEST_PASSED;
}


TEST (strpbrk_no_leaks) {
    const char *s = "hello";
    CHECK_STRING_CMP (strpbrk (s, "l"),==,"llo");
    TEST_PASSED;
}


TEST (strstr_no_leaks) {
    const char *s = "hello";
    CHECK_STRING_CMP (strstr (s, "lo"),==,"lo");
    TEST_PASSED;
}


TEST (strlen_no_leaks) {
    const char *s = "hello";
    CHECK_CMP (strlen (s),==,5);
    TEST_PASSED;
}


TEST (strerror_no_leaks) {
    CHECK_STRING_CMP (strerror (EINVAL),==,"Invalid argument");
    TEST_PASSED;
}


TEST (strtok_no_leaks) {
    char s[] = "hello,hello,hello";
    CHECK_STRING_CMP (strtok (s, ","),==,"hello");
    TEST_PASSED;
}


TEST (memcpy_no_leaks) {
    char out[10];
    memcpy (out, "hello", 6);
    CHECK_STRING_CMP (out,==,"hello");
    TEST_PASSED;
}


TEST (memmove_no_leaks) {
    char out[10];
    memmove (out, "hello", 6);
    CHECK_STRING_CMP (out,==,"hello");
    TEST_PASSED;
}


TEST (memcmp_no_leaks) {
    CHECK_CMP (memcmp ("hello", "hello", 6),==,0);
    TEST_PASSED;
}


TEST (memchr_no_leaks) {
    const char * s = "hello";
    CHECK (memchr (s, 'l', 4) == s+2);
    TEST_PASSED;
}


TEST (memset_no_leaks) {
    char out[10];
    out[5] = '\0';
    CHECK_STRING_CMP (memset (out, 'a', 5),==,"aaaaa");
    TEST_PASSED;
}


// ctype.h functions
TEST (math_no_leaks) {
    CHECK_CMP (sin (0),==,0);
    CHECK_CMP (cos (0),==,1);
    CHECK_CMP (tan (0),==,0);
    CHECK_CMP (sinh (1),==,1);
    CHECK_CMP (cosh (1),==,1);
    CHECK_CMP (tanh (1),==,0);
    CHECK_CMP (exp (0),==,1);
    CHECK_CMP (log (1),==,0);
    CHECK_CMP (log10 (1),==,0);
    CHECK_CMP (pow (2, 1),==,2);
    CHECK_CMP (sqrt (4),==,2);
    CHECK_CMP (ceil (4.3),==,5);
    CHECK_CMP (floor (4.3),==,4);
    CHECK_CMP (fabs (-4.3),==,4.3);
    CHECK_CMP (ldexp (4, 2),==,16);
    int x;
    CHECK_CMP (frexp (4.3, &x),==,0);
    double ip;
    CHECK_CMP (modf (4.3, &ip),==,0);
    CHECK_CMP (fmod (4.3, 4),==,0.3);
    CHECK_CMP (abs (-10),==, 10);
    CHECK_CMP (labs (-10),==, 10);
    div_t res = div (10, 2);
    CHECK_CMP (res.quot,==,5);
    CHECK_CMP (res.rem,==,0);
    ldiv_t res_l = ldiv (10, 2);
    CHECK_CMP (res_l.quot,==,5);
    CHECK_CMP (res_l.rem,==,0);
    TEST_PASSED;
}


// stdlib.h functions
TEST (stdlib_conversion_no_leaks) {
    CHECK_CMP (atof ("2.23"),==,2.23);
    CHECK_CMP (atoi ("2"),==,2);
    CHECK_CMP (atol ("2"),==,2);
    CHECK_CMP (strtod ("2.23", (char **) NULL),==,2.23);
    CHECK_CMP (strtol ("2", (char **)NULL, 10),==,2);
    CHECK_CMP (strtoul ("2", (char **)NULL, 10),==,2);
    TEST_PASSED;
}


TEST (rand_no_leaks) {
    srand (10);
    CHECK_CMP (rand (),==,1215069295);
    TEST_PASSED;
}


TEST (getenv_no_leaks) {
    char * p = getenv ("PWD");
    CHECK (p != NULL);
    TEST_PASSED;
}


TEST (qsort_no_leaks) {
    int array[] = {32, 1, 41, 0, 31, 13};
    qsort (array, 6, sizeof(int), int_comparator);
    for (int i = 1; i < 6; ++i)
	CHECK_CMP (array[i],>=,array[i-1]);
    TEST_PASSED;
}


TEST (bsearch_no_leaks) {
    int array[] = {0, 1, 2, 3, 10, 32};
    int key = 10;
    int * res = (int *) bsearch (&key, array, 6, sizeof(int), int_comparator);
    CHECK_CMP (*res,==,key);
    TEST_PASSED;
}


// time.h functions
TEST (time_no_leaks) {
    CHECK_CMP (clock (),!=,-1);
    CHECK_CMP (time (NULL),!=,-1);
    CHECK_CMP (difftime (12, 10),==,2);
    time_t t = time (NULL);
    struct tm * tm_val = gmtime (&t);
    CHECK (tm_val != NULL);
    CHECK (mktime (tm_val) != -1);
    CHECK (localtime (&t) != NULL);
    CHECK_STRING_CMP (asctime(localtime(&t)),==, ctime (&t));
    char buf[100];
    size_t size = strftime (buf, 100, "%I:%M:%S", tm_val);
    for (char * p = buf; p != buf + size; ++p)
	CHECK (isprint (*p));
    TEST_PASSED;
}


// stdio.h functions
static void write_fp (FILE *fp, const char *format, ...) {
    va_list ap;

    va_start (ap, format);
    vfprintf (fp, format, ap);
    va_end (ap);
}


static void read_fp (FILE *fp, const char *format, ...) {
    va_list ap;

    va_start (ap, format);
    vfscanf (fp, format, ap);
    va_end (ap);
}


TEST (basic_file_operations_no_leak) {
    char buf[100];
    FILE * fp = fopen ("/tmp/open_stlib_open", "w");
    CHECK (fp != NULL);
    CHECK_CMP (setvbuf(fp, NULL, _IONBF, 0),==,0);
    fputc('a', fp);
    putc('b', fp);
    fputs ("some line\n", fp);
    const char * line = "some line 2\n";
    fwrite (line, sizeof(char), strlen (line), fp);
    fprintf (fp, "testing %d\n", 10);
    write_fp (fp, "testing vfprintf %d\n", 11);

    fflush (fp);
    rewind (fp);
    fpos_t pos;
    CHECK_CMP (fgetpos (fp, &pos),==,0);
    CHECK_CMP (ftell (fp),!=,-1);
    rewind (fp);
    CHECK_CMP (fsetpos (fp, &pos),==,0);
    CHECK (fseek(fp, 0L, SEEK_SET) == 0);
    fclose (fp);
    fp = tmpfile ();
    setbuf(fp, NULL);
    CHECK_CMP (rename ("/tmp/open_stlib_open", "/tmp/open_stlib_open2"),==,0);
    CHECK (fp != NULL);

    fp = freopen("/tmp/open_stlib_open2", "r", fp);
    CHECK_CMP (fgetc (fp),==,'a');
    CHECK_CMP (getc (fp),==,'b');
    ungetc ('b', fp);
    CHECK_CMP (getc (fp),==,'b');
    fgets (buf, 11, fp);
    CHECK_STRING_CMP (buf,==,"some line\n");
    fread (buf, sizeof(char), strlen(line), fp);
    buf[strlen(line)] = '\0';
    CHECK_STRING_CMP (buf,==,line);
    int x;
    fscanf (fp, "testing %d\n", &x);
    CHECK_CMP (x,==,10);
    read_fp (fp, "testing vfprintf %d\n", &x);
    CHECK_CMP (x,==,11);
    CHECK_CMP (feof (fp),!=, 0);
    CHECK_CMP (ferror (fp),==, 0);
    clearerr (fp);
    fclose (fp);
    CHECK_CMP (remove ("/tmp/open_stlib_open2"),==,0);
    TEST_PASSED;
}


static void write_str (char *buf, const char *format, ...) {
    va_list ap;

    va_start (ap, format);
    vsprintf (buf, format, ap);
    va_end (ap);
}


static void read_str (char *buf, const char *format, ...) {
    va_list ap;

    va_start (ap, format);
    vsscanf (buf, format, ap);
    va_end (ap);
}

TEST (stdio_sprintf_scanf_no_leak) {
    char buf[100];
    sprintf (buf, "testing %d", 10);
    int x;
    sscanf (buf, "testing %d", &x);
    CHECK_CMP (x,==,10);
    write_str (buf, "testing vsprintf %d", 11);
    read_str (buf, "testing vsprintf %d", &x);
    CHECK_CMP (x,==,11);
    TEST_PASSED;
}



MAIN_TEST_DRIVER (ctype_no_leaks,
		  strcpy_no_leaks,
		  strncpy_no_leaks,
		  strcat_no_leaks,
		  strncat_no_leaks,
		  strcmp_no_leaks,
		  strncmp_no_leaks,
		  strchr_no_leaks,
		  strrchr_no_leaks,
		  strspn_no_leaks,
		  strcspn_no_leaks,
		  strcspn_no_leaks,
		  strpbrk_no_leaks,
		  strstr_no_leaks,
		  strlen_no_leaks,
		  strerror_no_leaks,
		  strtok_no_leaks,
		  memcpy_no_leaks,
		  memmove_no_leaks,
		  memcmp_no_leaks,
		  memchr_no_leaks,
		  memset_no_leaks,
		  math_no_leaks,
		  stdlib_conversion_no_leaks,
		  rand_no_leaks,
		  qsort_no_leaks,
		  bsearch_no_leaks,
		  time_no_leaks,
		  basic_file_operations_no_leak,
		  stdio_sprintf_scanf_no_leak);
