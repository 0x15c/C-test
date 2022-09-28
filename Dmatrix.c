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
#define max(a,b) a>b?a:b
// operations has different operands.
typedef struct Matrix{
    int col,row;
    float *mat;
}Matrix;
void malloc_mat(Matrix *tMat);
void free_mat(Matrix *tMat);
float DMdet(float *tMat, int dim);
float DMproduct(float *sMat, float *tMat);
float DMtrans(float *tMat);

void malloc_mat(Matrix *Mat)
{
    int block_size = Mat->col*Mat->row;
    Mat->mat = (float*) malloc(sizeof(float)*block_size);
}
float test_mat[2][3] = {{1.0f,2.0f,3.0f},{2.0f,1.0f,3.0f}};
Matrix test={
    .col=2,
    .row=3,
    .mat=&test_mat,
};
