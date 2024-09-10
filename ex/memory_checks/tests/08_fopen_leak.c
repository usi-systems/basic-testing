#include "basic_testing.h"
#include <stdio.h>




TEST (memory_leak) {
    FILE * fp = fopen("/tmp/leak_fopen", "w");
    fprintf (fp, "testing\n");
    TEST_PASSED;
}



MAIN_TEST_DRIVER (memory_leak);
