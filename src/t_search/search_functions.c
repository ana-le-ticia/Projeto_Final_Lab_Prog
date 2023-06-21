#include "search.h"

int proccess_arguments(int argc, char ** argv, Arguments * arguments){

    /* Default Arg Values */
    arguments->check_area = DEFAULT_AREA_VALUE;
    arguments->force_scale = 0;
    arguments->origin = 0;
    arguments->print_results = 1;
    arguments->test_file = NULL;

    arguments->tmp_path = (char *) malloc(sizeof(TMP_PATH)+1);
    sprintf(arguments->tmp_path, "%s", TMP_PATH);
    /* * */

    if(argc > 1)
        arguments->origin = 1;

    if(argc <= 2) return 1;

    char * split_arg = NULL;
    char * arg_value = NULL;

    for(int i = 1; i < argc; i++){

        if(!(strcmp(*(argv+i), "--no-print"))){
            arguments->print_results = 0;
            continue;
        }
        
        split_arg = strtok(*(argv+i), "=");
        arg_value = strtok(NULL, "=");

        if(!arg_value) continue;

        if(split_arg){
            if(!strcmp(split_arg, "--check-area")) arguments->check_area = atoi(arg_value);
            if(!strcmp(split_arg, "--tmp-path")) arguments->tmp_path = arg_value;
            if(!strcmp(split_arg, "--test-file")) arguments->test_file = arg_value;
            if(!strcmp(split_arg, "--force-scale")) arguments->force_scale = atoi(arg_value);
        }

    }

    return 1;
}

void log_crop(Crop crop, float current_pos, float max_pos){
    printf(WHTB""BBLU"\r$ >"BBLK" %*s "CRESET""BLKB""BBLU" %*.2f%%: (%*d, %*d) = %*.2f "CRESET, 15, crop.filename, 6, 100*(current_pos/max_pos), 4, crop.x, 4, crop.y, 8, crop.err);
    fflush(stdout);
}

int compare_results(DIR_FILES pgm_files, Crop * all_crops, char * test_file){
    
    FILE * positions_file = fopen(test_file, "r");
    if(!positions_file) return 0;

    char buffer[512];
    char * split_buffer = NULL;
    char filename[256];
    int xf, yf;

    printf(BLKB""BBLU"$ > Results: "CRESET"\n");
    while(fgets(buffer, 512, positions_file)){
        sprintf(filename, "%s", strtok(buffer, ", "));
        xf = atoi(strtok(NULL, ", "));
        yf = atoi(strtok(NULL, ", "));

        for(int k = 0; k < pgm_files.size; k++){
            if(!strcmp(filename, strtok((all_crops+k)->filename, "."))){
                if((all_crops+k)->x == xf && (all_crops+k)->y == yf){
                    printf(WHTB""BBLU"$ > "BGRN"%*s "CRESET""BLKB""BGRN" (%*d, %*d)"CRESET"\n", 15, (all_crops+k)->filename, 5, (all_crops+k)->x, 5, (all_crops+k)->y);
                }else{
                    printf(WHTB""BBLU"$ > "BRED"%*s "CRESET""BLKB""BRED" (%*d, %*d)"CRESET"\n", 15, (all_crops+k)->filename, 5, (all_crops+k)->x, 5, (all_crops+k)->y);
                }
                break;
            }
        }
    }

    fclose(positions_file);
    return 1;
}

int save_positions(char * filename, Crop * crops, unsigned size){

    FILE * save_file;
    save_file = fopen(filename, "w");

    if(!save_file) return 0;

    fprintf(save_file, "Filename, Position X, Position Y\n");
    for(int i = 0; i < size; i++){
        fprintf(save_file, "%s, %d, %d\n", strtok((crops+i)->filename, "."), (crops+i)->x, (crops+i)->y);
    }

    fclose(save_file);

    return 1;
}

void free_data(unsigned char ** data){
    if(data != NULL){
        free(*data);
        *data = NULL;
    }
}