#include <ctype.h>

#include "wcmp.h"

int wcmp(const char * a, const char * b) {
    while (*a != 0 && *b != 0) {
	if (!isalpha(*a)) {
	    ++a;
	} else if (!isalpha(*b)) {
	    ++b;
	} else {
	    do {
		if (*a < *b)
		    return -1;
		else if (*a > *b)
		    return 1;
		++a;
		++b;
	    } while (isalpha(*a) && isalpha(*b));
	    if (isalpha(*a))
		return 1;
	    if (isalpha(*b))
		return -1;
	}
    }
    for (; *a != 0; ++a)
	if (isalpha(*a))
	    return 1;

    for (; *b != 0; ++b)
	if (isalpha(*b))
	    return -1;

    return 0;
}

