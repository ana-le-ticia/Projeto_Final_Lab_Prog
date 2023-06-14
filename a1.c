#include <stdio.h>
#include <stdlib.h>
#include "convert_P5_to_P2.c"

#define SIZE 100

void convert_data(int w, int h, FILE* , FILE* );

int main(int argc, char ** argv){
    FILE * input_file;
    FILE * output_file;
    char file_name;
    int cut_width, cut_height, input_file_width, input_file_height;

    if (argc != 4){
        printf("Erro, quantidade errada de argumentos.\n");
    }

    file_name = atoi(argv[1]);
    cut_height = atoi(argv[2]);
    cut_width = atoi(argv[3]);

    input_file = fopen(file_name, "r");
    if (input_file == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fscanf(input_file, "%d %d\n", &input_file_width, &input_file_height);

    char linha[SIZE];
    while (fgets(linha, SIZE, input_file) != NULL) {
        printf("%s", linha);
    }

    if (linha[0] != 'P' || linha[1] != '2'){
        convert_data(input_file_width, input_file_height, input_file, output_file);
    }

    return 0;
}
