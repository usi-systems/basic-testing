#include <string.h>

#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p1 = new_processes();
    CHECK(p1);

    CHECK(add_from_file(p1, "tests/proc.txt"));

    struct query q;

    q.priority = 139;
    q.rss = 0;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    
    CHECK((r1 = search(p1, &q)));
    CHECK(strcmp(get_command(r1), "migration/0")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "watchdog/0")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "watchdog/1")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "migration/1")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "watchdog/2")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "migration/2")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "watchdog/3")==0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_command(r1), "migration/3")==0);
    CHECK(!(r1 = next(r1)));

    q.vsize = 1;

    CHECK(!(r1 = search(p1, &q)));

    q.vsize = -1;

    CHECK(!(r1 = search(p1, &q)));

    delete(p1);
    return 0;
}
