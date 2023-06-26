#include "util.h"

int proccess_arguments(int argc, char ** argv, Arguments * arguments){

    /* Default Arg Values */
    arguments->check_area = DEFAULT_AREA_VALUE;
    arguments->force_scale = 0;
    arguments->origin = NULL;
    arguments->output = NULL;
    arguments->print_results = 1;
    arguments->test_file = NULL;

    arguments->tmp_path = (char *) malloc(sizeof(TMP_PATH)+1);
    sprintf(arguments->tmp_path, "%s", TMP_PATH);

    arguments->match_method = REQM;
    arguments->compare_method = dissimilarity;
    /* * */

    char * arg = NULL;
    char * value = NULL;
    for(int i = 1; i < argc; i++){

        arg = *(argv+i);

        if(!strcmp(arg, "-h") || !strcmp(arg, "--help")) return HELP_ARG;

        if(!(strcmp(arg, "--no-print")) || !(strcmp(arg, "-n"))){
            arguments->print_results = 0;
            continue;
        }

        if(i+1 < argc){

            value = *(argv+i+1);

            if(!(strcmp(arg, "--image")) || !(strcmp(arg, "-i"))){
                arguments->origin = value;
                i++;
                continue;
            }

            if(!(strcmp(arg, "--output")) || !(strcmp(arg, "-o"))){
                arguments->output = value;
                i++;
                continue;
            }

            if(!(strcmp(arg, "--check-area")) || !(strcmp(arg, "-ac"))){
                arguments->check_area = atoi(value);
                i++;
                continue;
            }

            if(!(strcmp(arg, "--tmp-path")) || !(strcmp(arg, "-tmp"))){
                arguments->tmp_path = value;
                i++;
                continue;
            }

            if(!(strcmp(arg, "--test-file")) || !(strcmp(arg, "-tf"))){
                arguments->test_file = value;
                i++;
                continue;
            }

            if(!(strcmp(arg, "--force-scale")) || !(strcmp(arg, "-s"))){
                arguments->force_scale = atoi(value);
                i++;
                continue;
            }


            if(!strcmp(arg, "--use") || !strcmp(arg, "-u")){

                for(int i = 0; i < strlen(value); i++)
                    *(value+i) = tolower(*(value+i));

                if(!strcmp(value, "em")){
                    arguments->match_method = EM;
                    arguments->compare_method = dissimilarity;
                }
                if(!strcmp(value, "eqm")){
                    arguments->match_method = EQM;
                    arguments->compare_method = dissimilarity;
                }
                if(!strcmp(value, "ssim")){
                    arguments->match_method = SSIM;
                    arguments->compare_method = similarity;
                }
                if(!strcmp(value, "ncc")){
                    arguments->match_method = NCC;
                    arguments->compare_method = similarity;
                }
                if(!strcmp(value, "psnr")){
                    arguments->match_method = PSNR;
                    arguments->compare_method = similarity;
                }
                i++;
                continue;
            }

        }

        if(*(*(argv+i)) == '-')
            return INVALID_ARGS;
    }

    return VALID_ARGS;
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
        fprintf(save_file, "%s, %d, %d\n", strtok(crops[i]->filename, "."), crops[i]->x, crops[i]->y);
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

void print_help(char * bin){
    printf("\n:.Hello.:\n");
    printf("\nusage: %s -i `image_path`\n\n", bin);
    printf("option flags:\n");
    printf("-n, --no-print   \t block print progress.\n");
    printf("-s, --force-scale\t force origin image scale.\n");
    printf("-tf, --test-file \t compare found positions with any csv file.\n");
    printf("-o, --output     \t save found positions.\n");
    printf("-u, --use        \t use similiraty or dissimilarity method [ssim, em, eqm, reqm, psnr, ncc].\n");
    printf("-ac, --check-area\t change approx. area after resize.\n");
    printf("-tmp, --tmp-path \t select crop's path location.\n\n");
}

int similarity(double newValue, double oldValue){
    if(newValue > oldValue)
        return 1;
    return 0;
}
int dissimilarity(double newValue, double oldValue){
    if(newValue < oldValue)
        return 1;
    return 0;
}
