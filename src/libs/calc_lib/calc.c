#include "calc.h"

double EM(Image origin, Image crop, int init_x, int init_y){

    if(init_x > origin.w - crop.w || init_y > origin.h - crop.h) 
        return INVALID_DSTY_VALUE;

    double em = 0;
    double dist = 0;

    int x = init_x, y = init_y;
    int index = (y * origin.w) + x;

    for(int i = 0; i < crop.h*crop.w; i++){

        index = (y * origin.w) + x;
        if(i > 0 && (i%crop.w) == 0){
            y++;
            x = init_x;
        }

        dist = abs((*(crop.data+ i)) - (*(origin.data + index)));
        em += dist;

        x++;
    }

    em /= (double)(crop.w*crop.h);

    return em;
}

double EQM(Image origin, Image crop, int init_x, int init_y){

    if(init_x > origin.w - crop.w || init_y > origin.h - crop.h) 
        return INVALID_DSTY_VALUE;

    double eqm = 0;
    double dist = 0;

    int x = init_x, y = init_y;
    int index = (y * origin.w) + x;

    for(int i = 0; i < crop.h*crop.w; i++){
        
        index = (y * origin.w) + x;
        if(index >= (origin.w*origin.h)) continue;

        if(i > 0 && (i%crop.w) == 0){
            y++;
            x = init_x;
        }

        dist = (*(crop.data+ i)) - (*(origin.data + index));
        eqm += (dist * dist);

        x++;
    }

    eqm /= (double) (crop.w*crop.h);

    return eqm;
}

double REQM(Image origin, Image crop, int init_x, int init_y){

    if(init_x > origin.w - crop.w || init_y > origin.h - crop.h) 
        return INVALID_DSTY_VALUE;

    double eqm = 0;
    double dist = 0;

    int x = init_x, y = init_y;
    int index = (y * origin.w) + x;

    for(int i = 0; i < crop.h*crop.w; i++){

        index = (y * origin.w) + x;
        if(index >= (origin.w*origin.h)) continue;

        if(i > 0 && (i%crop.w) == 0){
            y++;
            x = init_x;
        }
        dist = (*(crop.data+ i)) - (*(origin.data + index));
        eqm += (dist * dist);
        x++;
    }

    eqm /= (double) (crop.w*crop.h);
    double reqm = sqrt(eqm);

    return reqm;
}

double NCC(Image origin, Image crop, int init_x, int init_y){
    
    if(init_x > origin.w - crop.w || init_y > origin.h - crop.h) 
        return INVALID_STY_VALUE;

    double pearson = 0;

    double mean1 = 0.0, mean2 = 0.0;
    double var1 = 0.0, var2 = 0.0, covar = 0.0;
    double diff1 , diff2;

    int x = init_x, y = init_y;
    int index = (y * origin.w) + x;

    for(int i = 0; i < crop.h*crop.w; i++){

        index = (y * origin.w) + x;
        if(i > 0 && (i%crop.w) == 0){
            y++;
            x = init_x;
        }

        mean1 += (double) (*(crop.data+i));
        mean2 += (double) (*(origin.data + index));

        x++;
    }

    mean1 /= (crop.w*crop.h);
    mean2 /= (crop.w*crop.h);

    x = init_x; y = init_y;
    index = (y * origin.w) + x;

    for(int i = 0; i < crop.h*crop.w; i++){

        index = (y * origin.w) + x;
        if(i > 0 && (i%crop.w) == 0){
            y++;
            x = init_x;
        }

        diff1 = *(crop.data+i) - mean1;
        diff2 = *(origin.data+index) - mean2;

        var1 += diff1 * diff1;
        var2 += diff2 * diff2;
        covar += diff1 * diff2;

        x++;
    }

    var1 /= (crop.w * crop.h - 1);
    var2 /= (crop.w * crop.h - 1);
    covar /= (crop.w * crop.h - 1);

    pearson = covar / (double) sqrt(var1*var2);

    return pearson;
}

double PSNR(Image origin, Image crop, int init_x, int init_y){

    if(init_x > origin.w - crop.w || init_y > origin.h - crop.h) 
        return INVALID_STY_VALUE;

    double eqm = EQM(origin, crop, init_x, init_y);

    double psnr = (double) 10 * log10((double) (crop.max*crop.max) / eqm);

    return psnr;
}

double SSIM(Image origin, Image crop, int init_x, int init_y)
{

    if(init_x > origin.w - crop.w || init_y > origin.h - crop.h) 
        return INVALID_STY_VALUE;

    double L = 255.0;
    double C1 = (0.01 * L) * (0.01 * L);
    double C2 = (0.03 * L) * (0.03 * L);

    unsigned int width = crop.w;
    unsigned int height = crop.h;
    unsigned char * data1 = crop.data;
    unsigned char * data2 = origin.data;


    double mean1 = 0.0, mean2 = 0.0;
    double var1 = 0.0, var2 = 0.0, covar = 0.0;

    // Calculate means, variances, and covariance
    int x = init_x, y = init_y;
    int index = y * origin.w + x;

    for (unsigned int i = 0; i < height*width; i++) {

        index = y * origin.w + x;

        if(i > 0 && (i%width) == 0){
            y++;
            x = init_x;
        }

        mean1 += data1[i];
        mean2 += data2[index];

        x++;
    }

    mean1 /= (width * height);
    mean2 /= (width * height);

    x = init_x;
    y = init_y;
    for (unsigned int i = 0; i < height*width; i++) {

        index = y * origin.w + x;
        if(i > 0 && (i%width) == 0){
            y++;
            x = init_x;
        }

        double diff1 = data1[i] - mean1;
        double diff2 = data2[index] - mean2;
        var1 += diff1 * diff1;
        var2 += diff2 * diff2;
        covar += diff1 * diff2;

        x++;
    }

    var1 /= (width * height - 1);
    var2 /= (width * height - 1);
    covar /= (width * height - 1);

    // Calculate SSIM
    double ssim = ((2 * mean1 * mean2 + C1) * (2 * covar + C2)) / ((mean1 * mean1 + mean2 * mean2 + C1) * (var1 + var2 + C2));

    return ssim;
}