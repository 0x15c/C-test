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
Matrix DMtrans(Matrix *tMat)
{
    int i,j,tmp=0;
    int block_size = tMat->col*tMat->row;
    Matrix mat_ans;
    mat_ans.mat_index = (Dtype*)malloc(sizeof(Dtype)*block_size);
    //ask for allocated mem space
    for(i=0;i<tMat->row;i++)
    {
        for(j=0;j<tMat->col;j++)
        {
            mat_ans.mat_index[i+j*tMat->row]=tMat->mat_index[j+i*tMat->col];
        }// temp_matrix[j,i]=target_matrix[i,j]
    }
    mat_ans.row=tMat->col;
    mat_ans.col=tMat->row;
    return mat_ans;
    
}
Matrix DMmultiply(Matrix *s1Mat, Matrix *s2Mat)
{
    int p = 0;
    Matrix DMret;
    DMret.mat_index=NULL;
    if ((p = s1Mat->col) != s2Mat->row)
    return DMret; //check if the operation is legal, if not, return a NULL.

    int i,j,k,l;
    int block_size = s1Mat->row*s2Mat->col;
    //Dtype *mat_index = NULL;
    //mat_index = (Dtype*)malloc(sizeof(Dtype)*block_size);
    
    DMret.row=s1Mat->row;
    DMret.col=s2Mat->col;

    DMret.mat_index = (Dtype*)malloc(sizeof(Dtype)*block_size);
    for(i=0;i<DMret.row;i++)
    {
        for(j=0;j<DMret.col;j++)
        {
            DMret.mat_index[i*DMret.row+j]=0;

            for(k=0;k<p;k++)
            {  
                DMret.mat_index[i*DMret.row+j]+=s1Mat->mat_index[i*s1Mat->col+k] * s2Mat->mat_index[k*s2Mat->col+j];
            }
        }
    }
    return DMret;
}
Matrix DMaugment(Matrix *s1Mat, Matrix *s2Mat)
{// link 2 Matrices by column, which requires those have the same cloumns.
    Matrix DMaug;
    DMaug.mat_index=NULL;
    if ((DMaug.row=s1Mat->row) != s2Mat->row)
    return DMaug;

    int i,j;
    DMaug.col = s1Mat->col + s2Mat->col;
    int block_size = DMaug.row*DMaug.col;
    DMaug.mat_index = (Dtype*)malloc(sizeof(Dtype)*block_size);
    for(i=0;i<DMaug.row;i++)
    {
        for(j=0;j<s1Mat->col;j++)
        {
            DMaug.mat_index[j+i*DMaug.col] = s1Mat->mat_index[j+i*s1Mat->col];
        }
        for(j>=s1Mat->col;j<DMaug.col;j++)
        {
            DMaug.mat_index[j+i*DMaug.col] = s2Mat->mat_index[j-s1Mat->col+i*s1Mat->col];
        }
    }
    return DMaug;
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
void DMfree(int num, Dtype *ap, ...)
{
    va_list arglist;
    va_start(arglist, ap);
    Dtype *garbage;
    for(int i=0;i<num;i++)
    {
        garbage = va_arg(arglist,Dtype*);
        free(garbage);
    }
    va_end(arglist);
}
