#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p = new_processes();
    CHECK(p);
    delete(p);
    return 0;
}
