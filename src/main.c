#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "ERROR: Please specify a path do the dataset\n");
        return -1;
    } 
    
    const char *file_path = argv[1];
    fprintf(stderr, "INFO: Data file specified: '%s'\n", file_path);
    
    return 0;
}
