#include "basic_testing.h"
#include <stdio.h>



TEST (memory_leak) {
    FILE *fp = tmpfile ();
    fprintf (fp, "testing\n");
    TEST_PASSED;
}




MAIN_TEST_DRIVER (memory_leak);
