#ifndef SIG_LOADING_H_DYN
#define SIG_LOADING_H_DYN

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_PATHLEN 400
#define MAX_LINELEN 100
#define DEFAULT_FILEPATH "/src/data/DIT-SHM-dataset.csv"
#define SHIFTED_ID 1
#define SIG_LENGTH 16384

typedef struct {
    int id;
    int reference[SIG_LENGTH];
    int shifted[SIG_LENGTH];
} sig_pair;


FILE *open_csv(const char *file_path);

int load_signals(sig_pair *signals, FILE *fd, int id);

#endif
