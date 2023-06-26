#ifndef __CROP_H__
#define __CROP_H__
#include "../libs/img_lib/img_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void filtroMedia(Image *imagem, int tamanhoJanela);

int cut_image(const Image *image, Image *image_cut, int width, int height);

#endif