extern int __real_main(int, char*[]);
#include <stdio.h>
#include <string.h>

#define filename(ext) \
   char ext##_filename[128] = {0}; \
   strncat( ext##_filename, __FILE__, strlen(__FILE__)-1); \
   strcat(ext##_filename, #ext)

int __wrap_main() {
    // Generate filenames
    // TODO: find good buffer size
    filename(in);
    filename(out);
    filename(expected);

    if (freopen(in_filename, "r", stdin) == NULL) {
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
    if ((outfile = freopen(out_filename, "w", stdout)) == NULL) {
       perror("freopen() failed");
       return 1;
    }
    int result = __real_main(2, (char*[]) {"diamond", "10"});
    fclose(outfile);
    
    // load files and compare outputs, char by char
    // TODO: check that everything works!
    if ((outfile = fopen(out_filename, "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s\n", out_filename);
        return 1;
    }
    FILE * exfile = fopen(expected_filename, "r");
    if (exfile == NULL) {
        fprintf(stderr, "Failed to open file %s\n", expected_filename);
        return 1;
    }
    int out_ch, ex_ch, row, column = 0;
    for(int i=0; 
        (out_ch = fgetc(outfile)) != EOF 
        && (ex_ch = fgetc(exfile)) != EOF; 
    ++i) {
        if (out_ch != ex_ch) {
            fprintf(stderr, "Output char \"%c\" different from expected char \"%c\"\n%s:%d:%d\ncheck respective I/O files for differences\n", 
            out_ch, ex_ch, out_filename,row, column);
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
    remove(out_filename);
    fclose(outfile);
    fclose(exfile);
    return result;
}
