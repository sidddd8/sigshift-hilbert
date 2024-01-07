#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "sig_loading_st.h"
#include "sig_utils.h"
#include "test_cases_signals.c"

char* parse_args(int argc, char *argv[]) {
    char* file_path;
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
    (void)fprintf(stderr, "INFO: Working data file: '%s'\n", file_path);
    (void)fprintf(stderr, "INFO: Signal static max size = %d\n", SIG_LENGTH);
    
    FILE* fd = open_csv(file_path);
    if (fd == NULL) {
        (void)fprintf(stderr, "ERR: Couldnt open file at '%s'\nQUITTING\n", file_path);
        return 0;
    }
    sig_pair signals;

    if (load_signals(&signals, fd, SHIFTED_ID) == EXIT_FAILURE) {
        (void)fprintf(stderr, "ERR: Failed loading singal values\nQUITTING\n");
        return 0;
    }
    else {
        (void)fprintf(stderr, "INFO: Succesfuly read and loaded signal values\n");
    }
    fclose(fd);
    complex test1[len_tests];
    copy_signal(test1, test_cases[0], len_tests);
    for (int i = 0; i < n_tests; ++i) {
        fprintf(stderr, "SIGNAL:\n");
        print_signal(test_cases[i], len_tests);
        fprintf(stderr, "\n");

        fprintf(stderr, "HILBERT:\n");
        hilbert(test_cases[i], len_tests);
        print_signal(test_cases[i], len_tests);
        fprintf(stderr, "\n");
        fprintf(stderr, "-------------------\n");
    }
    return 0;
}
