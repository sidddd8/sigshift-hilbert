#include "sig_loading_st.h"

FILE *open_csv(const char* file_path) {
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

int load_signals(sig_pair* signals, FILE* fd, int id) {
    signals->id = id;
    char row[MAX_LINELEN];
    
    char *token;
    bool file_end = false;
    for (int row_num = 0; row_num < SIG_LENGTH; ++row_num) {
        if (fgets(row, MAX_LINELEN, fd) == NULL) {
            file_end = true;
        }
       // first line (line 0) is the header of the .csv
        if (row_num >= 1) {
            if (file_end == true) {
                signals->reference[row_num-1].re = 0;
                signals->reference[row_num-1].im = 0;
                signals->shifted[row_num-1].re = 0;
                signals->shifted[row_num-1].im = 0;
            }
            else {
                token = strtok(row, ";");
                
                signals->reference[row_num-1].re = atoi(token);
                signals->reference[row_num-1].im = 0;
                
                int tok_id = 1;
                while(token != NULL) {
                    token = strtok(NULL, ";");
                    if (tok_id == id) {
                        signals->shifted[row_num-1].re = atoi(token);
                        signals->shifted[row_num-1].im = 0;
                    }
                    tok_id++;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

