/**
 * @file Dmatrix.h
 * @author 0x15c l12212788889@live.com
 * @brief header file for DMatrix, the toy matrix library
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) a>b?a:b
// operations like transpose only need 1 operands, but commonly most need 2 or more.
typedef struct Matrix{
    int col,row;
    float *mat_index;// To hold the matrix as a 1-dimensional array.
}Matrix;// A matrix must be clarified once it has been decleared.
float DMdet(Matrix *tMat);
float DMmultiply(Matrix *s1Mat, Matrix *s2Mat, Matrix *tMat);
void DMtrans(Matrix *tMat);
void DMprint(Matrix *tMat);
void DMupper(Matrix *tMat);