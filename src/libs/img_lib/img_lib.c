#include "./img_lib.h"

int PGM_save(char * name, char * path, Image img){
    FILE * file;

    char dir[256];
    sprintf(dir, "%s/%s.pgm", path, name);

    switch(img.type){
        case 2:
            file = fopen(dir, "w");
            break;
        case 5:
            file = fopen(dir, "wb");
            break;
    }

    if(!file) return 0;

    fprintf(file, "P%d\n%d %d\n%d\n", img.type, img.w, img.h, img.max);
    
    int max_value = img.max;
    int margin = 3;

    switch(img.type){
        case 2:
            while(max_value > 10){
                margin+=1;
                max_value /= 10;
            } 
            for(int i = 0; i < img.w * img.h; i++){
                if(i != 0 && (i%img.w) == 0) fprintf(file, "\n");
                fprintf(file, "%*d", margin, *(img.data+i));
            }
            break;
        case 5:
            fwrite(img.data, sizeof(unsigned char), img.h*img.w, file);
            break;
    }

    fclose(file);

    return 1;
}

int PGM_load(char * path, Image * save){

    FILE * image_file;

    image_file = fopen(path, "rb");
    
    if(!image_file) return 0;

    if(getc(image_file) != 'P') return 0;

    int type = getc(image_file) - 48;
    fseek(image_file, 1, SEEK_CUR);

    if(getc(image_file) == '#'){
        fscanf(image_file, "%s", save->first_comment);
        fseek(image_file, 1, SEEK_CUR);
    }else{
        fseek(image_file, -1, SEEK_CUR);
        sprintf(save->first_comment, " ");
    }

    while(getc(image_file) == '#'){
        while(getc(image_file) != '\n') continue;
    }
    fseek(image_file, -1, SEEK_CUR);

    fscanf(image_file, "%d %d", &(save->w), &(save->h));
    fscanf(image_file, "%d", &(save->max));

    save->type = type;
    save->data = (unsigned char *) malloc(sizeof(unsigned char) * save->h * save->w); 

    fseek(image_file, 1, SEEK_CUR);
    switch(type){
        case 2:
            for(int i = 0; i < save->h * save->w; i++){
                fscanf(image_file, "%hhd", save->data+i);
            }
            break;
        case 5:
            fread(save->data, sizeof(unsigned char), save->h * save->w, image_file);
            break;
    }
	
    fclose(image_file);

    return 1;
}

void PGM_square_crop(unsigned size, int x, int y, Image origin, Image * save){
    save->type = origin.type;
    save->w = size;
    save->h = size;
    save->max = origin.max;

    save->data = (unsigned char *) malloc(sizeof(unsigned char) * size*size);

    int x2 = x;
    int y2 = y;	

    for(int i = 0; i < save->w * save->h; i++){
        if(i > 0 && (i % save->w) == 0){
            y2++;
            x2 = x;
        }
        if(x2 >= origin.w || y2 >= origin.h)
            *(save->data+i) = 0;
        else *(save->data+i) = *(origin.data + (y2 * origin.w) + x2);
        x2++;
    }
}

void PGM_resize(Image origin, Image * save, int scale){

    int w = origin.w/scale;
    int h = origin.h/scale;

    save->type = origin.type;
    save->h = h;
    save->w = w;
    save->max = origin.max;
    save->data = (unsigned char *) malloc(sizeof(unsigned char) * w*h);

    int x = 0, y = 0;
    for(int i = 0; i < w*h; i++){

        if(i > 0 && (i%w) == 0){
            y++;
            x = 0;
        }

        *(save->data+i) = *(origin.data + ((y*scale) * origin.w) + x*scale);

        x++;
    }
}