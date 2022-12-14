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
    memMgmt *heap = DMinit();
    // starting with a declaration of heap memory, which indicates the start of the linklist
    Dtype test_mat[4][4] = {
        {2.0f, 4.0f, 8.0f, 16.0f},
        {0.5f, 0.25f, 0.125f, 0.0625f},
        {6.0f, 2.5f, 4.5f, 12.0f},
        {3.5f, 2.7f, 9.3f, 0.8f},
    };
    Matrix test = {
        .row = 4,
        .col = 4,                     // must be declared by hand
        .mat_index = &test_mat[0][0], // set the pointer on the first entry of matrix
    };
    DMprint(&test);
    Matrix trans = DMtrans(&test);
    printf("\n");
    Matrix ans = DMmultiply(&trans, &test);
    printf("\n");
    DMprint(&ans);
    ans = DMaugment(&trans, &trans);
    Matrix ans2 = DMaugment(&ans, &ans);
    printf("\n");
    printf("%d\n", mem_usage);
    Matrix ans3 = DMZeros(4);
    DMprint(&ans3);
    Matrix ansans = DMtrans(&ans2);
    DMprint(&ansans);
    free_pList(heap);
    // ending with a free function.
    return 0;
}