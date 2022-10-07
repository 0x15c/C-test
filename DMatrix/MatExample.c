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
    pList = DMinit();
    Dtype test_mat[3][4] = {
        {2.0f,4.0f ,8.0f  ,16.0f  },
        {0.5f,0.25f,0.125f,0.0625f},
        {6.0f,2.5f ,4.5f   ,12.0f },// those are "integers" for float32 type.
    };
    Matrix test={
        .row=3,
        .col=4,//must be declared by hand
        .mat_index=&test_mat[0][0],// set the pointer on the first entry of matrix
    };
    DMprint(&test);
    Matrix trans = DMtrans(&test);
    printf("\n");
    //DMprint(&trans);
    Matrix ans = DMmultiply(&trans,&test);
    printf("\n");
    DMprint(&ans);
    //DMfree_single(ans);// before modifying ans, free the allocated memory first. Otherwise it may cause a memory leak.
    ans = DMaugment(&trans,&trans);
    printf("\n");
    DMprint(&ans);
    
    //heap memory must be freed before exit.
    //DMfree(2,ans,trans);
    printf("%d",mem_usage);
    free_pList();
    return 0;
}