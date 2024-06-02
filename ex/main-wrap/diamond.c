#include <stdio.h>
#include <stdlib.h>

void print_diamond(int n) {
    for (int i = 1; i <= n; ++i) {
	for (int j = n - i; j > 0; --j)
	    putchar(' ');
	for (int j = 1; j < 2*i; ++j)
	    putchar('#');
	putchar('\n');
    }
    for (int i = n-1; i >= 1; --i) {
	for (int j = n - i; j > 0; --j)
	    putchar(' ');
	for (int j = 1; j < 2*i; ++j)
	    putchar('#');
	putchar('\n');
    }
}

int main(int argc, char * argv[]) {
    int n = 10;
    if (argc > 1)
	n = atoi(argv[1]);
    print_diamond(n);
}
