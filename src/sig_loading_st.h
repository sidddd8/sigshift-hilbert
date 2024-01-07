#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "sig_utils.h"
#include "SIG_CONFIG.h"

typedef struct {
    int id;
    int n;
    complex reference[SIG_LENGTH];
    complex shifted[SIG_LENGTH];
} sig_pair;


FILE *open_csv(const char* file_path);

int load_signals(sig_pair* signals, FILE* fd, int id);
