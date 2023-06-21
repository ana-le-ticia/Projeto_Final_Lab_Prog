
#include "calc.h"

float EM(Image origin, Image crop, int x, int y){

    float em = 0;

    if(x > origin.w - crop.w) return 9990;
    if(y > origin.h - crop.h) return 9990;

    int x2 = x, y2 = y;

    for(int i = 0; i < crop.h*crop.w; i++){

        if(i > 0 && (i%crop.w) == 0){
            y2++;
            x2 = x;
        }

        em += (pow((*(crop.data+ i)) - (*(origin.data + (y2*origin.w) + x2)), 2))/(float)(crop.w*crop.h);
        x2++;
    }

    return em;
}

float EQM(Image origin, Image crop, int x, int y){

    float eqm = 0;

    if(x > origin.w - crop.w) return 9990;
    if(y > origin.h - crop.h) return 9990;

    int x2 = x, y2 = y;
    for(int i = 0; i < crop.h*crop.w; i++){

        if(((y2*origin.w) + x2) >= (origin.w*origin.h)) continue;

        if(i > 0 && (i%crop.w) == 0){
            y2++;
            x2 = x;
        }

        eqm += (pow((*(crop.data+ i)) - (*(origin.data + (y2*origin.w) + x2)), 2))/(crop.w*crop.h);
        x2++;
    }

    return eqm;
}

float REQM(Image origin, Image crop, int x, int y){

    float eqm = 0;

    if(x > origin.w - crop.w) return 9990;
    if(y > origin.h - crop.h) return 9990;

    int x2 = x, y2 = y;
    for(int i = 0; i < crop.h*crop.w; i++){

        if(((y2*origin.w) + x2) >= (origin.w*origin.h)) continue;

        if(i > 0 && (i%crop.w) == 0){
            y2++;
            x2 = x;
        }

        eqm += (pow((*(crop.data+ i)) - (*(origin.data + (y2*origin.w) + x2)), 2))/(crop.w*crop.h);
        x2++;
    }

    float reqm = sqrt(eqm);

    return reqm;
}

float Pearson(Image origin, Image crop, int x, int y){

    if(x > origin.w - crop.w) return -12211221;
    if(y > origin.h - crop.h) return -12211221;

    float pearson = 0;

    float sum_x = 0, average_x = 0;
    float sum_j = 0, average_j = 0;
    float sum_h = 0;

    int x2 = x, y2 = y;
    for(int i = 0; i < crop.h*crop.w; i++){
        if(i > 0 && (i%crop.w) == 0){
            y2++;
            x2 = x;
        }
        average_j += (*(origin.data + (y2*origin.w) + x2))/(crop.h*crop.w);
        average_x += (*(crop.data+i))/(crop.h*crop.w);
        x2++;
    }

    x2 = x; y2 = y;
    for(int i = 0; i < crop.h*crop.w; i++){
        if(i > 0 && (i%crop.w) == 0){
            y2++;
            x2 = x;
        }
    
        sum_h += (*(crop.data+i) - average_x) * (*(origin.data + (y2*origin.w) + x2) - average_j)/  (float) (crop.h*crop.w -1);
        sum_x += (*(crop.data+i) - average_x)/ (float) (crop.h*crop.w -1);
        sum_j += (*(origin.data + (y2*origin.w) + x2) - average_j)/ (float) (crop.h*crop.w -1);

        x2++;
    }

    pearson = sum_h / sqrt(pow(sum_x, 2) * pow(sum_j, 2));

    return pearson;
}

float PSNR(Image origin, Image crop, int x, int y){

    float eqm = 0;

    if(x > origin.w - crop.w) return -1;
    if(y > origin.h - crop.h) return -1;

    int x2 = x, y2 = y;
    for(int i = 0; i < crop.h*crop.w; i++){

        if(((y2*origin.w) + x2) >= (origin.w*origin.h)) continue;

        if(i > 0 && (i%crop.w) == 0){
            y2++;
            x2 = x;
        }

        eqm += (pow((*(crop.data+ i)) - (*(origin.data + (y2*origin.w) + x2)), 2))/(crop.w*crop.h);
        x2++;
    }

    float psnr = 20 * log10((double) crop.max / (double) sqrt(eqm));

    return psnr;
}