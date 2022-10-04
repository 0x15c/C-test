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
int main()
{
    float test_mat[3][4] = {
        {2.0f,4.0f ,8.0f  ,16.0f  },
        {0.5f,0.25f,0.125f,0.0625f},
        {6.0f,10.0f,12.0f ,14.0f  },// those are "integers" for float32 type.
    };
    Matrix test={
        .col=4,
        .row=3,//must be declared by hand
        .mat_index=&test_mat[0][0],// set the pointer on the first entry of matrix
    };
    DMprint(&test);
    DMtrans(&test);
    DMprint(&test);
    return 0;
}