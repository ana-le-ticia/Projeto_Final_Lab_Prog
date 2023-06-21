#ifndef __IMG_LIB_H__
#define __IMG_LIB_H__

#include <stdio.h>
#include <stdlib.h>

/* PGM Image Struct */
typedef struct image Image;
struct image{
    short type;
    unsigned w;
    unsigned h;
    unsigned max;
    unsigned char * data;
    char first_comment[256];
};

/* Save PGM file */
int PGM_save(char * name, char * path, Image img);

/* Load PGM file */
int PGM_load(char * path, Image * save);

/* Resize Image */
void PGM_resize(Image origin, Image * save, int scale);

/* Crop A Square Area From Origin Image */
void PGM_square_crop(unsigned size, int x, int y, Image origin, Image * save);

#endif /* __IMG_LIB_H__ */