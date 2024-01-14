#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#include "sig_loading_st.h"
#include "test_cases_signals.c"
#include "processing.h"

int TEST_CASE = 0; // leave at 0 for any input file other than the test file

char* parse_args(int argc, char *argv[]) {
    char* file_path;
    if (TEST_CASE == 1) {
        file_path = TEST_FILEPATH;
    }
    else {
        if (argc == 1) {
            file_path = DEFAULT_FILEPATH;
        } 
        else {
            file_path = argv[1];
        }
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


    clock_t begin;
    clock_t end;
    double time_spent_EV;
    double time_spent_alg;
    float phase_shift[signals.n];

    begin = clock();
    (void)signal_EV(signals.shifted, signals.n);
    end = clock();
    time_spent_EV = (double)(end - begin) / CLOCKS_PER_SEC;
    (void)fprintf(stderr, "\nTime spent calculating the EV of a signal: %fs\n", time_spent_EV);

    begin = clock();
    float shift_EV = determine_phase_shift(phase_shift, signals.reference, signals.shifted, signals.n); 
    end = clock();
    time_spent_alg = (double)(end - begin) / CLOCKS_PER_SEC;
    (void)fprintf(stderr, "Time spent performing the algorithm: %fs\n", time_spent_alg);
    double scale = time_spent_alg/time_spent_EV;
    (void)fprintf(stderr, "Scaling of %f\n", scale);


    (void)fprintf(stderr, "\nEV of the shift is %f PI[rad]\n\n", shift_EV);
    char fname[30];
    if (TEST_CASE == 1) {
        sprintf(fname, "shifts/test_case.csv");
    }
    else {
        sprintf(fname, "shifts/id_%d.csv", signals.id);
    }
    
    (void)fprintf(stderr, "saved as '%s'\n", fname);
    write_into_csv(phase_shift, signals.n, fname);

    return 0;
}
