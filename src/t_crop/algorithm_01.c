
#include "../libs/img_lib/img_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void filtroMedia(Image *imagem, int tamanhoJanela) {
    int metadeJanela = tamanhoJanela / 2;

    unsigned char *pixelsOriginais = imagem->data;
    unsigned char *pixelsFiltrados = (unsigned char *)malloc(imagem->w * imagem->h * sizeof(unsigned char));

    for (int i = 0; i < imagem->h; i++) {
        for (int j = 0; j < imagem->w; j++) {
            int soma = 0;
            int count = 0;

            for (int k = -metadeJanela; k <= metadeJanela; k++) {
                for (int l = -metadeJanela; l <= metadeJanela; l++) {
                    int row = i + k;
                    int col = j + l;

                    if (row >= 0 && row < imagem->h && col >= 0 && col < imagem->w) {
                        soma += pixelsOriginais[row * imagem->w + col];
                        count++;
                    }
                }
            }

            pixelsFiltrados[i * imagem->w + j] = soma/(tamanhoJanela*tamanhoJanela);
        }
    }

    free(imagem->data);
    imagem->data = pixelsFiltrados;
}

int cut_image(const Image *image, Image *image_cut, int width, int height) {
  srand(time(NULL));
  int x, y, original_index, cropped_index;

  image_cut->w = width;
  image_cut->h = height;
  image_cut->max = image->max;
  image_cut->data = (unsigned char *)malloc(sizeof(unsigned char) *
                                            (image_cut->w * image_cut->h));

  x = rand() % (image->w - width + 1);
  y = rand() % (image->h - height + 1);

  for (int i = 0; i < image_cut->h; i++) {
    for (int j = 0; j < image_cut->w; j++) {
      original_index = (y + i) * image->w + (x + j);
      cropped_index = i * width + j;
      image_cut->data[cropped_index] = 1;
    }
  }

  return 1;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  char *file_name, *diretorio;
  int cut_width, cut_height, cut_quant;

  if (argc != 6) {
    printf("Erro, quantidade errada de argumentos.\n");
  }

  file_name = argv[1];
  diretorio = argv[2];
  cut_height = atoi(argv[2]);
  cut_width = atoi(argv[3]);
  cut_quant = atoi(argv[4]);

  Image image;
  image.data = NULL;
  if (!PGM_load(file_name, &image)) {
    perror("Erro");
    return 1;
  }

  char cropped_file[256];

  Image image_cut;
  image_cut.data = NULL;
  int x, y;

  FILE * coordenadas_origem;
  coordenadas_origem = fopen("robson.csv", "w");
  fprintf(coordenadas_origem, "nome do arquivo, posição x, posição y\n");
  for (int i = 0; i < cut_quant; i++) {
    
    x = rand() % (image.w - 100 + 1);
    y = rand() % (image.h - 100 + 1);
    PGM_square_crop(100, x, y, image, &image_cut);

    filtroMedia(&image_cut, 3);

    sprintf(cropped_file, "Crop_%d", i);

    if (!PGM_save(cropped_file, diretorio, image_cut)) {
      perror("Erro");
    }

    fprintf(coordenadas_origem, "%s, %d, %d\n", cropped_file, x, y);
      
    free(image_cut.data);
  }

  fclose(coordenadas_origem);

  return 0;
}
