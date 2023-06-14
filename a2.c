#include <stdio.h>
#include <stdlib.h>

// #define MAX 20
#define SIZE 200

int main(int argc, char ** argv){
    FILE * input_file;
    FILE * input_file_P2;
    char file_name, linha[SIZE];

    if(argc != 4){
        printf("Erro, quantidade errada de argumentos.\n");
        exit(1);
    }

    file_name = atoi(argv[1]);

    input_file = fopen(file_name, "r");
    if (input_file == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fscanf(input_file, "%d %d\n", &input_file_width, &input_file_height);

    while (fgets(linha, SIZE, input_file) != NULL) {
        printf("%s", linha);
    }

    if (linha[0] != 'P' || linha[1] != '2'){
        unsigned char *data = (unsigned char *)malloc(input_file_width * input_file_height);
        fread(data, sizeof(unsigned char), input_file_width * input_file_height, input_file);

        for (int i = 0; i < (input_file_width * input_file_height); i++){
            printf(output_file, "%u", data[i]);
        }
    free(data);
    }

    return 0;
}