extern int __real_main(int, char*[]);
#include <stdio.h>
#include <string.h>

int __wrap_main() {
    // Generate filenames
    // TODO: find good buffer size
    char* basefilename = __FILE__;
    char outfilename[128] = {0};
    char exfilename[128] = {0};
    strncat(outfilename, basefilename, strlen(basefilename)-1);
    strncat(exfilename, basefilename, strlen(basefilename)-1);
    strcat(outfilename, "out");
    strcat(exfilename, "expected");

    // redirect stdout to file
    FILE *outfile;
    if ((outfile = freopen(outfilename, "w", stdout)) == NULL) {
       perror("freopen() failed");
       return 1;
    }
    int result = __real_main(2, (char*[]) {"diamond", "10"});
    fclose(outfile);
    
    // compare outputs, char by char
    // TODO: check that everything works!
    outfile = fopen(outfilename, "r");
    FILE * exfile = fopen(exfilename, "r");
    int out_ch, ex_ch, row, column = 0;
    for(int i=0; 
        (out_ch = fgetc(outfile)) != EOF 
        && (ex_ch = fgetc(exfile)) != EOF; 
    ++i) {
        if (out_ch != ex_ch) {
            fprintf(stderr, "Output char \"%c\" different from expected char \"%c\"\n%s:%d:%d\ncheck respective I/O files for differences\n", 
            out_ch, ex_ch, outfilename,row, column);
            return 1;
        }
        ++column;
        if (out_ch == '\n') {
            ++row;
            column = 0;
        }
    }
    remove(outfilename);
    return result;
}
