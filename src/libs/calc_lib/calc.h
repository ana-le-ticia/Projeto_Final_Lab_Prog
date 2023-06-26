#ifndef __CALC_LIB_H__
#define __CALC_LIB_H__

#include "../img_lib/img_lib.h"
#include <math.h>
#include <stdlib.h>

#define INVALID_STY_VALUE -1
#define INVALID_DSTY_VALUE 99999999

/* Compare Images Using ME */
double EM(Image origin, Image crop, int init_x, int init_y);

/* Compare Images Using MSE */
double EQM(Image origin, Image crop, int init_x, int init_y);

/* Compare Images Using RMSE */
double REQM(Image origin, Image crop, int init_x, int init_y);

/* Compare Images Using PSNR */
double PSNR(Image origin, Image crop, int init_x, int init_y);

/* Compare Images Using NCC */
double NCC(Image origin, Image crop, int init_x, int init_y);

/* Compare Images Using SSIM */
double SSIM(Image origin, Image crop, int init_x, int init_y);

#endif /* __CALC_LIB_H__ */