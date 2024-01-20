#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "tuls.h"



// struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//              ino_t      d_ino;                /* file number of entry */
//              __uint16_t d_reclen;             /* length of this record */
//              __uint8_t  d_type;               /* file type, see below */
//              __uint8_t  d_namlen;             /* length of string in d_name */
//              char    d_name[255 + 1];   /* name must be no longer than this */
//      };

void simpleLsFunction() {
    DIR *dirp;
    struct dirent *entryName;
    //struct stat statName;

    dirp = opendir(".");
    while ((entryName = readdir(dirp)) != NULL) {
        // printf("%s\n", entryName -> d_name);
        if (entryName -> d_name[0] !=  '.') {
            printf("%s\n", entryName -> d_name);
        }
    }
    closedir(dirp);
}

void filesGivenDirectory(char *argument, int space) {
    DIR *dirp;
    struct dirent *entryName;
    struct stat statName;
    char path[1000];

    

    dirp = opendir(argument);
    if (dirp == NULL) {
        fprintf(stderr, "Error opening the directory %s: %s\n", argument, strerror(errno));
    }

    // for (int i = 0; i < space; i++) {
    //     printf("   ");
    // }
    if (space == 0) {
        printf("%s\n", argument);
    }

    while ((entryName = readdir(dirp)) != NULL) {
        //printf("%s\n", entryName -> d_name);

        if (strcmp(entryName->d_name, ".") == 0 || strcmp(entryName->d_name, "..") == 0) {
            //printf("%s\n", entryName -> d_name);
            //strcpy(path, entryName -> d_name);
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", argument, entryName -> d_name);
        // created a new path for the directory. 

        for (int i = 0; i < space + 1; i++) {
            printf("   ");
        }
        printf("current path = %s\n", path);
        printf("%s\n", entryName->d_name); // prints every file in directory
       

        if (stat(path, &statName) != 0) {
            fprintf(stderr, "stat() error on %s: %s\n", path, strerror(errno));
        } else if (S_ISDIR(statName.st_mode)) {
            //printf("**%s\n", path);
            filesGivenDirectory(path, space+1);
        } 

    }
    closedir(dirp);
}

