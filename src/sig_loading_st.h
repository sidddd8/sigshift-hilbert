#ifndef SIG_LOADING_H_DYN
#define SIG_LOADING_H_DYN

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "sig_utils.h"
#include "sig_config.h"

typedef struct {
    int id;
    complex reference[SIG_LENGTH];
    complex shifted[SIG_LENGTH];
} sig_pair;


FILE *open_csv(const char* file_path);

int load_signals(sig_pair* signals, FILE* fd, int id);

#endif
