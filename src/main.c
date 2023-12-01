#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "sig_loading.h"


char* parse_args(int argc, char *argv[]) {
    char *file_path;
    if (argc == 1) {
        file_path = DEFAULT_FILEPATH;
    } 
    else {
        file_path = argv[1];
    }
    return file_path;
}


int main(int argc, char *argv[]) {
    
    const char *file_path = parse_args(argc, argv);
    fprintf(stderr, "INFO: Working data file: '%s'\n", file_path);

    FILE *fd = open_csv(file_path);
    if (fd == NULL) {
        fprintf(stderr, "ERR: Couldnt open file at '%s'\nQUITTING\n", file_path);
        return 0;
    }
    sig_pair signals;

    if (load_signals(&signals, fd, SHIFTED_ID) == EXIT_FAILURE) {
        fprintf(stderr, "ERR: Failed loading singal values\nQUITTING\n");
        return 0;
    }
    else {
        fprintf(stderr, "INFO: Succesfuly read and loaded signal values\n");
        fprintf(stderr, "INFO: Signals are of length %d\n", signals.sig_len);
    }

    free(signals.reference);
    free(signals.shifted);
    fclose(fd);
    
    return 0;
}
