#ifndef __CALC_LIB_H__
#define __CALC_LIB_H__

#include "../img_lib/img_lib.h"
#include <math.h>
#include <stdlib.h>

/* Compare Images Using ME */
float EM(Image origin, Image crop, int x, int y);

/* Compare Images Using MSE */
float EQM(Image origin, Image crop, int x, int y);

/* Compare Images Using RMSE */
float REQM(Image origin, Image crop, int x, int y);

/* Compare Images Using PSNR */
float PSNR(Image origin, Image crop, int x, int y);

/* Compare Images Using Pearson */
float Pearson(Image origin, Image crop, int x, int y);

#endif /* __CALC_LIB_H__ */