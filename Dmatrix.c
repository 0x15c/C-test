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
    float *mat_index;
}Matrix;
void malloc_mat(Matrix *tMat);
void free_mat(Matrix *tMat);
float DMdet(Matrix *tMat, int dim);
float DMproduct(Matrix *sMat, float *tMat);
void DMtrans(Matrix *tMat);

// void malloc_mat(Matrix *Mat)
// {
//     int block_size = Mat->col*Mat->row;
//     Mat->mat_index = (float*) malloc(sizeof(float)*block_size);
    
// }

void DMtrans(Matrix *tMat)
{
    int i,j=0;
    int block_size = tMat->col*tMat->row;
    float *mat_index;
    //mat_index = (float *) malloc(sizeof(float)*block_size);
    // tmpMat->col = tMat->row;
    // tmpMat->row = tMat->col;
    //malloc_mat(tmpMat);
    //*(&tmpMat->mat_index+(0+0*tMat->row)*sizeof(float)) = (float*)(&tMat->mat_index+(0+0*tMat->col)*sizeof(float));
    for(i=0;i<tMat->col;i++)
    {
        for(j=0;j<tMat->row;j++)
        {
            *(&mat_index+(j+i*tMat->row)*sizeof(float)) = (float*)(&tMat->mat_index+(i+j*tMat->col)*sizeof(float));
        }
    }
    for(i=0;i<block_size;i++)
    {
        *(&tMat->mat_index+i)=*(&mat_index+i);
    }
}


//-------------------------examples-------------------------
