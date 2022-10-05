/**
 * @file MatExample.c
 * @author 0x15c l12212788889@live.com
 * @brief the basic examples of my Matrix process lib.
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "Dmatrix.h"
#include "DMatrix.c"
#ifndef Dtype
    #define Dtype float
    /**
     * @brief for universal usage, replace float with double, uint32, ...
     * already defined in "DMatrix.h"
     */
#endif
int main()
{
    Dtype test_mat[2][4] = {
        {2.0f,4.0f ,8.0f  ,16.0f  },
        {0.5f,0.25f,0.125f,0.0625f},// those are "integers" for float32 type.
    };
    Matrix test={
        .col=4,
        .row=2,//must be declared by hand
        .mat_index=&test_mat[0][0],// set the pointer on the first entry of matrix
    };
    DMprint(&test);
    Matrix trans = DMtrans(&test);
    printf("\n");
    DMprint(&trans);
    Matrix ans = DMmultiply(&trans,&test);
    printf("\n");
    DMprint(&ans);


    free(trans.mat_index);
    free(ans.mat_index);
    return 0;
}