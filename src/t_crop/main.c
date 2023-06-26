#include "./util.h"

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