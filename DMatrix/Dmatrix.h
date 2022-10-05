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
#ifndef __Dmatrix_h_
#define __Dmatrix_h_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) a>b?a:b
#define Dtype float// for universal usage, replace float with double, uint32, ...
// operations like transpose only need 1 operands, but commonly most need 2 or more.
typedef struct Matrix{
    int col,row;
    Dtype *mat_index;// To hold the matrix as a 1-dimensional array.
}Matrix;// A matrix must be clarified once it has been decleared.
Dtype DMdet(Matrix *tMat);
//Matrix* DMmalloc();
Matrix DMmultiply(Matrix *s1Mat, Matrix *s2Mat);
Matrix DMtrans(Matrix *tMat);
void DMprint(Matrix *tMat);
void DMupper(Matrix *tMat);

#endif