#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdio.h>
#include <time.h>
#include "../libs/dir_lib/dir.h"
#include "../libs/calc_lib/calc.h"
#include "../libs/img_lib/img_lib.h"

#define TMP_PATH "./tmp"
#define DEFAULT_AREA_VALUE 25

/* Colors */
#define BBLK "\e[1;30m"
#define BBLU "\e[1;34m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define WHTB "\e[47m"
#define BLKB "\e[40m"
#define CRESET "\e[0m"

/* in-line Arguments Struct */
typedef struct proccess_arguments Arguments;
struct proccess_arguments{
    short origin;
    short print_results;
    int force_scale;
    int check_area;
    char * test_file;
    char * tmp_path;
};

/* Found Crop Struct */
typedef struct crop Crop;
struct crop{
    int x;
    int y;
    float err;
    char * filename;
};

/* Proccess Prompt Arguments */
int proccess_arguments(int argc, char ** argv, Arguments * arguments);

/* Show Crop Proccess */
void log_crop(Crop crop, float current_pos, float max_pos);

/* Compare Found Results With Original File */
int compare_results(DIR_FILES pgm_files, Crop * all_crops, char * test_file);

/* Save Found Positions */
int save_positions(char * filename, Crop * crops, unsigned size);

/* Free Unsigned Char Vector Data */
void free_data(unsigned char ** data);

#endif /* __SEARCH_H__ */