#include <string.h>

#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p1 = new_processes();
    CHECK(p1);

    CHECK(add_from_file(p1, "tests/proc.txt"));

    struct query q;

    q.priority = 0;
    q.rss = 0;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    struct query_result * r2;
    
    int count = 0;

    for (r1 = search(p1, &q); r1 != 0; r1 = next(r1))
	count += 1;

    CHECK_INT_CMP(count,==,284);

    struct processes * p2 = new_processes();
    CHECK(p2);

    CHECK(add_from_file(p2, "tests/proc1.txt"));
    CHECK(add_from_file(p2, "tests/proc2.txt"));
    
    r1 = search(p1, &q);
    r2 = search(p2, &q);

    count = 0;
    while (r1 && r2) {
	CHECK(get_pid(r1) == get_pid(r2));
	CHECK(get_ppid(r1) == get_ppid(r2));
	CHECK(strcmp(get_user(r1), get_user(r2)) == 0);
	CHECK(get_priority(r1) == get_priority(r2));
	CHECK(get_cpu_usage(r1) == get_cpu_usage(r2));
	CHECK(get_rss(r1) == get_rss(r2));
	CHECK(get_size(r1) == get_size(r2));
	CHECK(get_vsize(r1) == get_vsize(r2));
	CHECK(strcmp(get_command(r1), get_command(r2)) == 0);
	r1 = next(r1);
	r2 = next(r2);
    }
    CHECK(!r1);
    CHECK(!r2);

    clear(p1);
    CHECK(search(p1, &q) == 0);
    
    count = 0;
    for (r2 = search(p2, &q); r2 != 0; r2 = next(r2))
	count += 1;

    CHECK_INT_CMP(count,==,284);

    clear(p2);
    CHECK(search(p2, &q) == 0);

    delete(p1);
    delete(p2);
    return 0;
}
