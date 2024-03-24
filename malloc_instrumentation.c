#include <assert.h>

#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// TODO: check if problematic for forked tests?
static size_t max_allocations = 1;

#define SET_ALLOC(value) max_allocations = value

#define CHECK_ALLOC(expected) do {  \
	if ((expected) != max_allocations) {			\
	    printf("\n%s:%d: Allocation assertion failed\n     expected '"#expected"'; found %lu\n", \
		   __FILE__, __LINE__, max_allocations);	\
	    return 0;					                \
	}	                                            \
    } while (0)

int *dummy_test() {
    SET_ALLOC(0);
    printf("%s", "a random string");
    SET_ALLOC(1);
    int *p = malloc(sizeof(int));
    CHECK_ALLOC(0);
    free(p);
    CHECK_ALLOC(1);
}

int main(void)
{

    int *p = malloc(sizeof(int));

    if (p) {
	write(STDOUT_FILENO, "Allocated\n", strlen("Allocated\n"));
	free(p);
    } else write(STDOUT_FILENO, "Allocation failed\n", strlen("Allocation failed\n"));

    int *c = malloc(sizeof(int));
    if (c) {
	write(STDOUT_FILENO, "Unexpectedly Allocated\n", strlen("Unexpectedly  Allocated\n"));
    } else write(STDOUT_FILENO, "Allocation failed\n", strlen("Allocation failed\n"));

    int *s = malloc(sizeof(int));
    assert(!s);

    dummy_test();
    
}

void *malloc(size_t size)
{
    static void *(*libc_malloc)(size_t) = NULL;
    if (!libc_malloc) 
	libc_malloc = dlsym(RTLD_NEXT, "malloc");	

    if (max_allocations > 0) {
	--max_allocations;
	return libc_malloc(size);
    }
    
    return 0;
}

void free(void * ptr)
{ 
    static void (*libc_free)(void *) = NULL;
    if (!libc_free) 
	libc_free = dlsym(RTLD_NEXT, "free");	

    if (max_allocations > 0) {
	++max_allocations;
	return libc_free(ptr);
    }
}