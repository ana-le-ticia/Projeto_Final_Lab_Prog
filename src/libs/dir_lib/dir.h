#ifndef __DIR_LIB_H__
#define __DIR_LIB_H__

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct dir_files DIR_FILES;
struct dir_files{
    int size;
    char path[256];
    char ** files;
};

int DIR_get_by_type(char * dir, char * type, DIR_FILES * save_dir);

#endif /* DIR__LIB_H__ */