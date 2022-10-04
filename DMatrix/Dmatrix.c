/**
 * @file Dmatrix.c
 * @author 0x15c
 * @brief A wheel reinventing, toy-like matrix process lib for maybe MCUs,
 * including the basic operations for matrix, i.e. multiplication, gauss-
 * jordan elimation, determinate, transpose, inverse, ...
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Every one could modify this file since it is unlisenced.
 * 
 */
#include "Dmatrix.h"
void DMtrans(Matrix *tMat)
{
    int i,j,tmp=0;
    int block_size = tMat->col*tMat->row;
    float *mat_index = NULL;
    mat_index = (float*)malloc(sizeof(float)*block_size);
    //ask for allocated mem space
    for(i=0;i<tMat->row;i++)
    {
        for(j=0;j<tMat->col;j++)
        {
            mat_index[i+j*tMat->row]=tMat->mat_index[j+i*tMat->col];
        }// temp_matrix[j,i]=target_matrix[i,j]
    }
    for(i=0;i<block_size;i++)
    {
        tMat->mat_index[i]=mat_index[i];
    }// set target equal to temp
    free(mat_index);//free mem space
    tmp = tMat->col;
    tMat->col = tMat->row;
    tMat->row = tmp;//reset the info of columns and rows
}
void DMprint(Matrix *tMat)
{// a straightforward print function
    int i,j = 0;
    for(i=0;i<tMat->row;i++)
    {
        for(j=0;j<tMat->col;j++)
        {
            printf("[%d,%d]=%f ",i,j,tMat->mat_index[j+i*tMat->col]);
        }
        printf("\n");
    }
}
