extern int __real_main(int, char*[]);
#include <stdio.h>
#include <string.h>

int __wrap_main() {
    // Generate filenames
    // TODO: find good buffer size
    char* basefilename = __FILE__;
    char infilename[128] = {0};
    char outfilename[128] = {0};
    char exfilename[128] = {0};
    strncat(infilename, basefilename, strlen(basefilename)-1);
    strncat(outfilename, basefilename, strlen(basefilename)-1);
    strncat(exfilename, basefilename, strlen(basefilename)-1);
    strcat(infilename, "in");
    strcat(outfilename, "out");
    strcat(exfilename, "expected");

    if (freopen(infilename, "r", stdin) == NULL) {
        // TODO: check that error is no file, can ignore then, other
        perror("freopen() for stdin failed");
    }

    // Temporary test to showcase stdin redirection (from file)
    int ch;
    while((ch=getchar()) != EOF) {
        putchar(ch);
    }

    // redirect stdout to file
    FILE *outfile;
    if ((outfile = freopen(outfilename, "w", stdout)) == NULL) {
       perror("freopen() failed");
       return 1;
    }
    int result = __real_main(2, (char*[]) {"diamond", "10"});
    fclose(outfile);
    
    // load files and compare outputs, char by char
    // TODO: check that everything works!
    if ((outfile = fopen(outfilename, "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s\n", outfilename);
        return 1;
    }
    FILE * exfile = fopen(exfilename, "r");
    if (exfile == NULL) {
        fprintf(stderr, "Failed to open file %s\n", exfilename);
        return 1;
    }
    int out_ch, ex_ch, row, column = 0;
    for(int i=0; 
        (out_ch = fgetc(outfile)) != EOF 
        && (ex_ch = fgetc(exfile)) != EOF; 
    ++i) {
        if (out_ch != ex_ch) {
            fprintf(stderr, "Output char \"%c\" different from expected char \"%c\"\n%s:%d:%d\ncheck respective I/O files for differences\n", 
            out_ch, ex_ch, outfilename,row, column);
            fclose(outfile);
            fclose(exfile);
            return 1;
        }
        ++column;
        if (out_ch == '\n') {
            ++row;
            column = 0;
        }
    }
    remove(outfilename);
    fclose(outfile);
    fclose(exfile);
    return result;
}
