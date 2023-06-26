#include "./util.h"

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