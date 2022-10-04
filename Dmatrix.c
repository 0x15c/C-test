/**
 * @file Dmatrix.c
 * @author 0x15c
 * @brief A wheel reinventing matrix process lib for MCUs.
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Every one could modify this file since it is unlisenced.
 * 
 */
//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) a>b?a:b
// operations has different operands.
typedef struct Matrix{
    int col,row;
    float *mat_index;
}Matrix;
void malloc_mat(Matrix *tMat);
void free_mat(Matrix *tMat);
float DMdet(Matrix *tMat, int dim);
float DMproduct(Matrix *sMat, float *tMat);
void DMtrans(Matrix *tMat);
void DMprint(Matrix *tMat);

void DMtrans(Matrix *tMat)
{
    int i,j,tmp=0;
    int block_size = tMat->col*tMat->row;
    float *mat_index = NULL;
    mat_index = (float*)malloc(sizeof(float)*block_size);
    for(i=0;i<tMat->row;i++)
    {
        for(j=0;j<tMat->col;j++)
        {
            mat_index[i+j*tMat->row]=tMat->mat_index[j+i*tMat->col];
        }
    }
    for(i=0;i<block_size;i++)
    {
        tMat->mat_index[i]=mat_index[i];
    }
    free(mat_index);
    tmp = tMat->col;
    tMat->col = tMat->row;
    tMat->row = tmp;
}
void DMprint(Matrix *tMat)
{
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

//-------------------------examples-------------------------
