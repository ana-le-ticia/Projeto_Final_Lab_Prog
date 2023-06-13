#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_data(int w, int h, FILE* , FILE* );

int main(){

    FILE * in;
    FILE * out;

    char format[3];
    int width, height, maxValue;

    in = fopen("dog_P5.pgm", "rb");
    if(in == NULL){
        printf("Erro ao criar arquivo\n");
        exit(1);
    }
    
    fscanf(in, "%s\n", format);
    fscanf(in, "%d %d\n", &width, &height);
    fscanf(in, "%d\n", &maxValue);

    if (format[0] != 'P' || format[1] != '5'){
        printf("Formato de arquivo invalido\n");
        fclose(in);
        exit(1);
    }

    out = fopen("dog_P2.pgm", "w");
    if(out == NULL){
        printf("Erro ao abrir arquivo\n");
        fclose(in);
        exit(1);
    }

    fprintf(out, "P2\n");
    fprintf(out, "%d %d\n", width, height);
    fprintf(out, "%d\n", maxValue);

    convert_data(width, height, in, out);

    fclose(in);
    fclose(out);

    printf("Conversao concluida.\n");

    return 0;
}


void convert_data(int w, int h, FILE* input, FILE* output){
    unsigned char *data = (unsigned char *)malloc(w * h);
    fread(data, sizeof(unsigned char), w * h, input);
    for (int i = 0; i < (w * h); i++){
        fprintf(output, "%u", data[i]);
    }
    free(data);
}