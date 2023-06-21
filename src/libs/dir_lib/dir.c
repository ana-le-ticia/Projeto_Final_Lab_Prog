#include "dir.h"

int DIR_get_by_type(char * dir, char * type, DIR_FILES * save_dir){

    DIR * imgs_dir;
    imgs_dir = opendir(dir);

    if(!imgs_dir) return 0;

    int file_count = 0;
    struct dirent * img_file = readdir(imgs_dir);

    while(img_file != NULL){
        if(img_file->d_type == 8 && !strcmp((img_file->d_name + strlen(img_file->d_name)-4), type))
            file_count++;
        img_file = readdir(imgs_dir);
    }
    rewinddir(imgs_dir);

    save_dir->size = file_count;
    sprintf(save_dir->path, "%s", dir);

    save_dir->files = (char **) malloc(sizeof(char *) * file_count);
    if(!(save_dir->files)) return 0;

    for(int i = 0; i < file_count; i++){

        img_file = readdir(imgs_dir);
        if(img_file->d_type != 8 || strcmp((img_file->d_name + strlen(img_file->d_name)-4), type)){
            i--;
            continue;
        }

        (*(save_dir->files + i)) = (char *) malloc(sizeof(char) * 256);

        if(!(*(save_dir->files + i))){
            for(int j = i-1; j >= 0; j--) free((*(save_dir->files + j)));
            free(save_dir->files);
            return 0;
        }

        sprintf((*(save_dir->files + i)), "%s", img_file->d_name);
    }

    closedir(imgs_dir);

    return 1;
}