extern int __real_main(int, char*[]);

int __wrap_main() {
    char* argv[] = {"diamond", "0"};
    int result = __real_main(2, argv);
    return result;
}
