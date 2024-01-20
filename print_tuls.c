#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "tuls.h"

int main(int argc, char **argv) {
    printf("Number of arguments : %d\n", argc);


    if (argc == 1) {
        simpleLsFunction();
    } else {
        filesGivenDirectory(argv[1], 0);
    }

    if (argc > 2) {
        perror("The number of arguments was greater than 2");
        exit(EXIT_FAILURE);
    }
     
    return 0;
}
