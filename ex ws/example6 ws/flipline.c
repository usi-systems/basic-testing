#include <stdio.h>

int main() {
    char line[1000];
    int i = 0;

    for (int c = getchar(); c != EOF; c = getchar()) {
	if (c == '\n') {
	    while (i > 0) {
		--i;
		putchar(line[i]);
	    }
	    putchar('\n');
	} else {
	    if (i < 1000) {
		line[i] = c;
		++i;
	    }
	}
    }
    while (i > 0) {
	--i;
	putchar(line[i]);
    }
}
