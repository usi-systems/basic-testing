int stringequal(char * s1, char * s2) {
    while (*s1 != 0 || *s2 != 0) {
	if (*s1 != *s2)
	    return 0;
    }
    return 1;
}
