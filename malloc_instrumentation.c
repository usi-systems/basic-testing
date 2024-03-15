#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static size_t max_allocations = 1;

int main(void)
{

    int *p = malloc(sizeof(int));

    if (p) {
	write(STDOUT_FILENO, "Allocated\n", strlen("Allocated\n"));
	free(p);
    } else write(STDOUT_FILENO, "Allocation failed\n", strlen("Allocation failed\n"));

    int *s = malloc(sizeof(int));
    assert(!s);
    
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
