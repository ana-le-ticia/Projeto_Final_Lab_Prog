
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "convert_P5_to_P2.c"

#define SIZE 100

typedef struct {
    int width;
    int height;
    int maxValue;
    unsigned char * data;
} PGM_image;

PGM_image read_image(const char * file_name){
    FILE * input_img;
    char pgm_verifier[3];
    int img_width, img_height, max_value;

    input_img = fopen("file_name", "r");
    if (!input_img){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fscanf(input_img, "%2s", pgm_verifier);
    if(pgm_verifier[0] != 'P' || pgm_verifier[1] != '2'){
        printf("O arquivo não é uma imagem PGM valida\n");
        exit(1);
    }

    fscanf(input_img, "%d %d %d", &img_width, &img_height, &max_value);
    fgetc(input_img);

    PGM_image image;

    image.width = img_width;
    image.height = img_height;
    image.maxValue = max_value;
    image.data = (unsigned char*)malloc(image.width*image.height);

    fread(image.data, sizeof(unsigned char), image.width * image.height, input_img);

    fclose(input_img);

    return image;
}

//escreve os dados de uma estrutura pgm (imagem pgm) em um arquivo PGM
void write_image(const char * file_name, const PGM_image * image){
    FILE * img_file;
    img_file = fopen(img_file, "w");
    if(!file_name){
        printf("Erro ao criar arquivo.\n");
        exit(1);
    }

    fprintf(img_file, "P2\n%d %d\n %d\n", image->width, image->height, image->maxValue);
    fwrite(image->data, sizeof(unsigned char), image->width * image->height, img_file);

    fclose(img_file);
}

PGM_image cut_image(const PGM_image * image, int width, int height){
    srand(time(NULL));
    PGM_image image_cut;
    int x, y, original_index, cropped_index;

    image_cut.width = width;
    image_cut.height = height;
    image_cut.maxValue = image->maxValue;
    image_cut.data = (unsigned char *)malloc(image_cut.width * image_cut.height);

    x = rand() % (image->width - width+1);
    y = rand() % (image->height - height+1);

    for(int i = 0; i < image_cut.height; i++){
        for(int j = 0; j < image_cut.width; j++){
            original_index = (y + i) * image->width + (x + j);
            cropped_index = i * width + j;
            image_cut.data[cropped_index] = image->data[original_index];
        }
    }

    return image_cut;
}

int main(int argc, char * argv[]){
    srand(time(NULL));
    char file_name, output_file[20];
    int cut_width, cut_height, cut_quant;

    if (argc != 5){
        printf("Erro, quantidade errada de argumentos.\n");
    }

    file_name = atoi(argv[1]);
    cut_height = atoi(argv[2]);
    cut_width = atoi(argv[3]);
    cut_quant = atoi(argv[4]);

    PGM_image image = read_image(file_name);

    FILE * output_file = fopen("recortes.pgm", "w");
    if (output_file == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fprintf(output_file,"P2\n%d %d\n255\n", cut_width, cut_height * cut_quant);

    for(int i = 0; i < cut_quant; i++){
        PGM_image image_cut = cut_image(&image, cut_width, cut_height);

        fwrite(image_cut.data, sizeof(unsigned char), cut_width * cut_height, output_file);

        free(image_cut.data);
    }

    fclose(output_file);

    return 0;
}