#include "sig_loading_st.h"

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
    signals->id = id;
    char row[MAX_LINELEN];
    
    char *token;
    int num_lines = 0;
    while (feof(fd) != true) {
        if (fgets(row, MAX_LINELEN, fd) == NULL) {
            break;
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
    return EXIT_SUCCESS;
}
