#include <string.h>

#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p1 = new_processes();
    CHECK(p1);

    CHECK(add_from_file(p1, "tests/proc.txt"));

    struct query q;

    q.priority = 19;
    q.rss = -1;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    
    CHECK((r1 = search(p1, &q)));
    CHECK(strcmp(get_user(r1), "root") == 0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_user(r1), "root") == 0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_user(r1), "systemd+") == 0);
    CHECK((r1 = next(r1)));
    CHECK(strcmp(get_user(r1), "systemd+") == 0);
    CHECK((r1 = next(r1)));
    terminate_query(r1);

    q.priority = 19;
    q.rss = 0;
    q.size = 0;
    q.vsize = -2000000;
    q.cpu_usage = -1.0;
    
    CHECK((r1 = search(p1, &q)));

    CHECK(get_pid(r1) == 2331);
    CHECK(strcmp(get_command(r1), "firefox") == 0);
    CHECK((r1 = next(r1)));
    CHECK(get_pid(r1) == 2986);
    CHECK(strcmp(get_command(r1), "WebContent") == 0);
    CHECK(!(r1 = next(r1)));

    delete(p1);
    return 0;
}
