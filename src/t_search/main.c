#include "search.h"

int main(int argc, char **argv) {

    /* Start */
    clock_t t_init = clock();

    Arguments arguments;
    proccess_arguments(argc, argv, &arguments);

    //Get all files .pgm in TMP_PATH
    DIR_FILES pgm_files;
    if(!DIR_get_by_type(arguments.tmp_path, ".pgm", &pgm_files)){
        perror("\nFalha ao abrir o diretório");
        fprintf(stderr, "\n");
        return 1;
    }

    int r_scale = 1;
    Image origin, origin_r, crop, crop_r, minimum_area;
    origin.data = NULL;
    crop.data = NULL;
    origin_r.data = NULL;
    crop_r.data = NULL;
    minimum_area.data = NULL;

    char load_path[256] = {0};
    char current_image[256] = {0};

    // Load origin image from line argument.
    if(arguments.origin){
        sprintf(current_image, "%s", *(argv+1));
        PGM_load(current_image, &origin);
        if(!PGM_load(current_image, &origin)){
            fprintf(stderr, "\"%s\":\n", current_image);
            perror("Falha ao abrir a imagem de origem");
            fprintf(stderr, "\n");
            return 1;
        }
        PGM_resize(origin, &origin_r, r_scale);
    }

    Crop * all_crops = (Crop *) malloc(sizeof(Crop) * pgm_files.size);

    int x = 0, y = 0, fx = 0, fy = 0;
    float comp;
    if(arguments.force_scale) r_scale = arguments.force_scale;

    for(int k = 0; k < pgm_files.size; k++){

        (all_crops+k)->filename = *(pgm_files.files+k);
        (all_crops+k)->err = 999;
        (all_crops+k)->x = -1;
        (all_crops+k)->y = -1;

        //Load cropped image.
        sprintf(load_path, "./%s/%s", TMP_PATH, *(pgm_files.files+k));
        if(!PGM_load(load_path, &crop)){
            perror("\nFalha ao abrir arquivo");
            fprintf(stderr, "\n");
            continue;
        }

        //Load original image if not in the line arguments.
        if(!arguments.origin && strcmp(current_image, crop.first_comment)){
            if(!PGM_load(crop.first_comment, &origin)){
                fprintf(stderr, "\"%s\":\n", *(pgm_files.files+k));
                perror("\tFalha ao abrir a imagem de origem");
                fprintf(stderr, "\n");
                continue;
            }
            sprintf(current_image, "%s", crop.first_comment);
        }

        // Set scale for origin and crop if not entered --force-scale flag.  
        if(!arguments.force_scale){
            if(origin.w*origin.h >= 128*128) r_scale = 2;
            if(origin.w*origin.h >= 256*256) r_scale = 3;
            if(origin.w*origin.h >= 512*512) r_scale = 4;
            if(origin.w*origin.h >= 1024*1024) r_scale = 5;
        }

        if(crop.h/r_scale == 0 || crop.w/r_scale == 0){
            fprintf(stderr, "Erro ao redimensionar imagem: %s\n", *(pgm_files.files+k));
            continue;
        }

        PGM_resize(origin, &origin_r, r_scale);
        PGM_resize(crop, &crop_r, r_scale);

        PGM_square_crop(crop_r.w-1, 1, 1, crop_r, &minimum_area);

        if(!strcmp(current_image, "")){
            fprintf(stderr, "\"%s\":\n\tImagem de origem não encontrada!\n", *(pgm_files.files+k));
            continue;
        }

        x = 0;
        y = 0;

        for(int i = 0; i < origin_r.h*origin_r.w; i++){

            if(i > 0 && (i%origin_r.w) == 0){
                x = 0;
                y++;
            }

            comp = REQM(origin_r, minimum_area, x+1, y+1);

            if(comp < (all_crops+k)->err){
                (all_crops+k)->err = comp;
                (all_crops+k)->x = x*r_scale;
                (all_crops+k)->y = y*r_scale;
            }

            x++;

			if(arguments.print_results && (!(i%(origin_r.w*10)) || i == origin_r.w*origin_r.h-1))
                log_crop(*(all_crops+k), i, origin_r.h*origin_r.w);

        }

        (all_crops + k)->err = REQM(origin, crop, (all_crops+k)->x, (all_crops+k)->y);

        if(arguments.print_results) log_crop(*(all_crops+k), 1, 1);

        fx = (all_crops+k)->x;
        fy = (all_crops+k)->y;

        x = fx - arguments.check_area/2;
        y = fy - arguments.check_area/2;

        for(int i = 0; i < arguments.check_area*arguments.check_area; i++){

            if(i > 0 && (i%arguments.check_area) == 0){
                x = fx - arguments.check_area/2;
                y++;
            }
            
            comp = REQM(origin, crop, x, y);

            if(comp < (all_crops+k)->err){
                (all_crops+k)->err = comp;
                (all_crops+k)->x = x;
                (all_crops+k)->y = y;
            }

            x++;

			if(arguments.print_results && (!(i%(arguments.check_area)) || i == (arguments.check_area*arguments.check_area)-1))
                log_crop(*(all_crops+k), i, arguments.check_area*arguments.check_area);
        }

        if(arguments.print_results){
            log_crop(*(all_crops+k), 1, 1);
            printf("\n");
        }

        free_data(&crop.data);
        free_data(&crop_r.data);
        free_data(&origin_r.data);
        free_data(&minimum_area.data);
    }

    /* Show exec. time */
    clock_t t_end = clock();
    double elapsed_time = (double) (t_end - t_init)/CLOCKS_PER_SEC;
    printf("\nDone in %.2lfs.\n\n", elapsed_time);


    /* Saving found positions */
    if(!save_positions("found_positions.csv", all_crops, pgm_files.size)) 
        fprintf(stderr, "\nErro ao salvar arquivo de posições!\n");


    /* Compare results if --test-file flag was given. */
    if(arguments.test_file != NULL){
        if(!compare_results(pgm_files, all_crops, arguments.test_file)){
            fprintf(stderr, "Erro ao comparar resultados com o arquivo \"%s\"\n", arguments.test_file);
        }
    }


    return 0;
}