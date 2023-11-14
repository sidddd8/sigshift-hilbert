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

typedef struct {
    int id;
    int sig_len;
    int *reference;
    int *shifted;
} sig_pair;

FILE *open_csv(const char *file_path) {
    FILE *fd;
    char cwd[MAX_PATHLEN];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "ERR: Failed obtaining current working directory\n");
        return NULL;
    }
    fd = fopen(strcat(cwd, file_path), "r");
    if (fd == NULL) {
        fprintf(stderr, "ERR: Failed opening file '%s'\n", file_path);
        return NULL;
    }
    return fd;
}

int load_signals(sig_pair *signals, FILE *fd, int id) {
    int size = 750;
    signals->id = id;
    signals->reference = calloc(size, sizeof(int));
    signals->shifted = calloc(size, sizeof(int));
    if ((signals->reference == NULL) || (signals->shifted == NULL)) {
        fprintf(stderr, "ERR: Failed initial calloc for signal reference or shift\n");
        return EXIT_FAILURE;
    }

    char row[MAX_LINELEN];
    char *token;

    int num_lines = 0;
    while (feof(fd) != true) {
        if (fgets(row, MAX_LINELEN, fd) == NULL) {
            break;
        }
        if (num_lines >= size) {
            size *= 2;
            int *tmp_ref = realloc(signals->reference, size*sizeof(int));
            int *tmp_shift = realloc(signals->shifted, size*sizeof(int));
            if ((tmp_ref == NULL) || (tmp_shift == NULL)) {
                fprintf(stderr, "ERR: Failed realloc for signal reference or shift\n");
                return EXIT_FAILURE;
            }
            signals->reference = tmp_ref;
            signals->shifted = tmp_shift;
        }
        // first line (line 0) is the header of the .csv
        if (num_lines >= 1) {
            token = strtok(row, ";");
            signals->reference[num_lines-1] = atoi(token);
            
            int tok_id = 1;
            while(token != NULL) {
                token = strtok(NULL, ";");
                if (tok_id == id) {
                    signals->shifted[num_lines-1] = atoi(token);
                }
                tok_id++;
            }
        }
        num_lines++;
    }
    signals->sig_len = num_lines-1;
    return EXIT_SUCCESS;
}

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
    sig_pair signals;

    if (load_signals(&signals, fd, SHIFTED_ID) == EXIT_FAILURE) {
        fprintf(stderr, "ERR: Failed loading singal values\n");
    }
    else {
        fprintf(stderr, "INFO: Succesfuly read and loaded signal values\n");
    }

    free(signals.reference);
    free(signals.shifted);
    fclose(fd);
    
    return 0;
}
