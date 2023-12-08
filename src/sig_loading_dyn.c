#include "sig_loading_dyn.h"

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
    int size = 1024;
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
    signals->sig_len = size;
    //fprintf(stderr, "Size is %d",size);
    return EXIT_SUCCESS;
}
