#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main(int argc, char **argv){
    char *file_name;
    char linha[SIZE];
    int cut_width, cut_height;
    int input_file_width, input_file_height;

    FILE *input_file;
    FILE *output_file;

    if(argc != 4){
        printf("Error, quantidade errada de argumentos\n");
        exit(1);
    }

    file_name = argv[1];
    cut_width = atoi(argv[2]);
    cut_height = atoi(argv[3]);

    input_file = fopen(*file_name, "r");
    if (input_file == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fscanf(input_file, "%d %d \n", &input_file_width, &input_file_height);

    printf("%d %d", input_file_width, input_file_height);

    // while (fgets(linha, SIZE, input_file) != NULL) {
    //     printf("%s", linha);
    // }

    // if (linha[0] != 'P' || linha[1] != '2'){
    //     unsigned char *data = (unsigned char *) malloc (input_file_width * input_file_height);
    //     fread(data, sizeof(unsigned char), input_file_width * input_file_height, input_file);

    //     for (int i = 0; i < input_file_width * input_file_height; i++){
    //         fprintf(output_file, "%u", data[i]);
    //     }
    //     free(data);
    // }


    return 0;
}