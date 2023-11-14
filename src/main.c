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
    int *reference;
    int *shifted;
} sig_pair;

void load_signals(sig_pair *signals, const char *file_path, int id) {
    
    char cwd[MAX_PATHLEN];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "ERR: Failed obtaining current working directory\n");
    }

    FILE *fp;
    char row[MAX_LINELEN];
    char *token;

    fp = fopen(strcat(cwd, file_path), "r");
    if (fp == NULL) {
        fprintf(stderr, "ERR: Failed opening file '%s'\n", file_path);
        return;
    }

    while (feof(fp) != true) {
        if (fgets(row, MAX_LINELEN, fp) == NULL) {
            fprintf(stderr, "ERR: Failed reading a line in %s\n", file_path);
            return;
        }
        
        fprintf(stderr, "row is: %s\n", row);
        token = strtok(row, ";");
        while(token != NULL)
        {
            printf("Token: %s\n", token);
            token = strtok(NULL, ";");
        }
    }
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
    sig_pair signals;
    load_signals(&signals, file_path, SHIFTED_ID);
    
    
    
    return 0;
}
