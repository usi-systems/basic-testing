#include <vector>
#include <string>
#include <cctype>

#include "wcmp.h"

void read_vector (std::vector <std::string> & W, const char * s) {
    while (*s != 0) {
	if (isalpha(*s)) {
	    const char * begin = s;
	    ++s;
	    while (isalpha(*s))
		++s;
	    W.push_back(std::string (begin, s));
	} else
	    ++s;
    }
}

int wcmp(const char * a, const char * b) {
    std::vector <std::string> A;
    std::vector <std::string> B;
    read_vector(A, a);
    read_vector(B, b);
    
    for (size_t i = 0; i < A.size() && i < B.size(); ++i) {
	if (A[i] < B[i])
	    return -1;
	if (A[i] > B[i])
	    return 1;
    }
    if (A.size() < B.size())
	return -1;
    if (A.size() > B.size())
	return 1;
    return 0;
}
