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
// To free the memory allocated by malloc() during the process of a matrix operation automatically,
// a linklist is defined to maintain the address of those pointers,
// an initiate and a de-initiate function are designed for auto-freeing.
int mem_usage;         // count by Byte
memMgmt *pList = NULL; // a global variable for locating the element of linklist
memMgmt *DMinit()      // initiate the linklist
{
    memMgmt *init = (memMgmt *)malloc(sizeof(memMgmt));
    init->matrix_p = NULL;
    init->next = NULL;
    pList = init;
    return init;
}
memMgmt *DMadd_p(Dtype *pMat_index, memMgmt *link)
{
    memMgmt *link_next = (memMgmt *)malloc(sizeof(memMgmt));
    link->next = link_next;
    link_next->matrix_p = pMat_index;
    link_next->next = NULL;

    return link_next;
}
Matrix DMtrans(Matrix *tMat)
{
    int i, j, tmp = 0;
    int block_size = tMat->col * tMat->row;
    Matrix mat_ans;
    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    // ask for allocated mem space
    for (i = 0; i < tMat->row; i++)
    {
        for (j = 0; j < tMat->col; j++)
        {
            mat_ans.mat_index[i + j * tMat->row] = tMat->mat_index[j + i * tMat->col];
        } // temp_matrix[j,i]=target_matrix[i,j]
    }
    mat_ans.row = tMat->col;
    mat_ans.col = tMat->row;
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
Matrix DMmultiply(Matrix *s1Mat, Matrix *s2Mat)
{
    int p = 0;
    Matrix mat_ans;
    mat_ans.mat_index = NULL;
    if ((p = s1Mat->col) != s2Mat->row)
        return mat_ans; // check if the operation is legal, if not, return a NULL.

    int i, j, k, l;
    int block_size = s1Mat->row * s2Mat->col;

    mat_ans.row = s1Mat->row;
    mat_ans.col = s2Mat->col;

    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (i = 0; i < mat_ans.row; i++)
    {
        for (j = 0; j < mat_ans.col; j++)
        {
            mat_ans.mat_index[i * mat_ans.row + j] = 0;

            for (k = 0; k < p; k++)
            {
                mat_ans.mat_index[i * mat_ans.row + j] += s1Mat->mat_index[i * s1Mat->col + k] * s2Mat->mat_index[k * s2Mat->col + j];
            }
        }
    }
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
Matrix DMaugment(Matrix *s1Mat, Matrix *s2Mat)
{ // link 2 Matrices by column, which requires those have the same cloumns.
    Matrix mat_ans;
    mat_ans.mat_index = NULL;
    if ((mat_ans.row = s1Mat->row) != s2Mat->row)
        return mat_ans;

    int i, j;
    mat_ans.col = s1Mat->col + s2Mat->col;
    int block_size = mat_ans.row * mat_ans.col;
    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (i = 0; i < mat_ans.row; i++)
    {
        for (j = 0; j < s1Mat->col; j++)
        {
            mat_ans.mat_index[j + i * mat_ans.col] = s1Mat->mat_index[j + i * s1Mat->col];
        }
        for (j >= s1Mat->col; j < mat_ans.col; j++)
        {
            mat_ans.mat_index[j + i * mat_ans.col] = s2Mat->mat_index[j - s1Mat->col + i * s1Mat->col];
        }
    }
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
Matrix DMZeros(int dim)
{
    int block_size = dim * dim;
    Matrix mat_ans;
    mat_ans.col = dim;
    mat_ans.row = dim;
    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (int i = 0; i < block_size; i++)
    {
        mat_ans.mat_index[i] = 0.0f;
    }
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
Matrix DMIdenti(int dim)
{
    int block_size = dim * dim;
    Matrix mat_ans;
    mat_ans.col = dim;
    mat_ans.row = dim;
    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (int i = 0; i < block_size; i++)
    {
        mat_ans.mat_index[i] = 0.0f;
    }
    for (int i = 0; i <= dim; i++)
    {
        mat_ans.mat_index[(dim + 1) * i] = 1.0f;
    }
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
void DMprint(Matrix *tMat)
{ // a straightforward print function
    int i, j = 0;
    for (i = 0; i < tMat->row; i++)
    {
        for (j = 0; j < tMat->col; j++)
        {
            printf("[%d,%d]=%f ", i, j, tMat->mat_index[j + i * tMat->col]);
        }
        printf("\n");
    }
}
void DMfree_single(Matrix tMat)
{
    if (tMat.mat_index != NULL)
        free(tMat.mat_index);
    tMat.mat_index = NULL;
}
void free_pList(memMgmt *heap)
{
    pList = DMadd_p(NULL, pList);
    memMgmt *proc = heap;
    while (proc->next != NULL)
    {
        free(proc->matrix_p);
        proc->matrix_p = NULL;
        proc = proc->next;
    }
    free(heap);
    free(proc);
}