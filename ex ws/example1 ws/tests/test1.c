#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p = new_processes();
    CHECK(p);
    CHECK(add_from_file(p, "tests/proc.txt"));
    clear(p);
    delete(p);
    return 0;
}
