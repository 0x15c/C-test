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
#define MAX_MATRICES 200
#define max(a, b) ((a) > (b) ? (a) : (b))
#define _eps 0.00001f
#define Dtype float // for universal usage, replace float with double, uint32, ...
#define _is_equal(a, b) (fabs((a) - (b)) < _eps ? (1) : (0))
// operations like transpose only need 1 operands, but commonly most need 2 or more.
typedef struct Matrix
{
    int col, row;
    Dtype *mat_index; // To hold the matrix as a 1-dimensional array.
} Matrix;             // A matrix must be clarified once it has been decleared.
typedef struct memMgmt
{
    Dtype *matrix_p;
    struct memMgmt *next; // the struct of the memory management linklist
} memMgmt;
Dtype DMdet(Matrix *tMat);
// Matrix* DMmalloc();
Matrix DMmultiply(Matrix *s1Mat, Matrix *s2Mat);
Matrix DMaugment(Matrix *s1Mat, Matrix *s2Mat);
Matrix DMtrans(Matrix *tMat);
Matrix DMupper(Matrix *tMat);
Matrix DMInv(Matrix *tMat);
Matrix DMRef(Matrix *tMat);
Matrix DMZeros(int dim);
Matrix DMIdenti(int dim);

void DMrowch(Matrix *target, int i, int j);
void DMrowch_multi(Matrix *target, int *order);
int DMrowscale(Matrix *target, int i, int col);
void DMrowelim(Matrix *target, int i, int j);

Matrix DMIdenti(int dim);
Matrix DMZeros(int dim);

void DMprint(Matrix *tMat);

memMgmt *DMinit();
memMgmt *DMadd_p(Dtype *pMat_index, memMgmt *link);
void free_pList(memMgmt *heap);
void DMerrHandler();
int *rearrange(int *input, int arr_len);
#endif