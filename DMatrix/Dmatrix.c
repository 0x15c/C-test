/**
 * @file Dmatrix.c
 * @author 0x15c
 * @brief A wheel reinventing, toy-like matrix process lib for maybe MCUs,
 * including the basic operations for matrix, i.e. multiplication, gauss-
 * jordan elimation, determinant, transpose, inverse, ...
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Every one could modify this file since it is unlisenced.
 *
 */
#include "Dmatrix.h"
int mem_usage;         // count by Byte
Dtype det;             // a global variable to hold determinant
memMgmt *pList = NULL; // a global variable to locate the heap
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
void DMrowch(Matrix *target, int i, int j) // exchange the i-th and j-th row
{
    Dtype *tmp = (Dtype *)malloc(sizeof(Dtype) * target->col);
    for (int k = 0; k < target->col; k++)
    {
        tmp[k] = target->mat_index[k + i * target->col];
        target->mat_index[k + i * target->col] = target->mat_index[k + j * target->col];
    }
    for (int k = 0; k < target->col; k++)
    {
        target->mat_index[k + j * target->col] = tmp[k];
    }
    free(tmp);
}
void DMrowch_multi(Matrix *target, int *order) // read the preset order as reference, fill rows in a blank array.
{
    int block_size = target->col * target->row;
    Dtype *tmp = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (int i = 0; i < target->row; i++)
    {
        for (int j = 0; j < target->col; j++)
        {
            tmp[j + i * target->col] = target->mat_index[j + order[i] * target->col];
        }
    }
    for (int i = 0; i < block_size; i++)
    {
        target->mat_index[i] = tmp[i];
    }
    free(tmp);
}
int DMrowscale(Matrix *target, int i) // determine the pivot column and return its position
{
    int k, l = 0;
    Dtype scale = 0;
    for (k = 0; k < target->col; k++)
    {
        if (fabs(target->mat_index[k + i * target->col]) > _eps)
        {
            scale = target->mat_index[k + i * target->col];
            target->mat_index[k + i * target->col] = 1;
            for (l = k + 1; l < target->col; l++)
            {
                target->mat_index[l + i * target->col] /= scale;
            }
            det *= scale;
            return k; // position of first entry of non-zero column.
        }
    }
}
void DMrowelim(Matrix *target, int i, int j) // row j minus row i
{
    for (int k = 0; k < target->col; k++)
    {
        target->mat_index[k + j * target->col] -= target->mat_index[k + i * target->col];
    }
}
Matrix DMref(Matrix *tMat) // Gauss Elimination
{
    int i, j, k;
    int max = 0;
    det = 1;
    int *nzero_pos = (int *)malloc(sizeof(int) * tMat->row);
    for (j = 0; j < tMat->row; j++)
    {
        for (i = 0; i < tMat->row; i++)
        {
            nzero_pos[i] = DMrowscale(tMat, i);
        } // scale each column
        int *order = rearrange(nzero_pos, tMat->row);
        DMrowch_multi(tMat, order);
        for (k = j + 1; (k < tMat->row) && (nzero_pos[order[k]] == j); k++)
        {
            DMrowelim(tMat, j, k);
        }
    }
    Matrix mat_ans;
    mat_ans.row = tMat->row;
    mat_ans.col = tMat->col;
    mat_ans.mat_index = tMat->mat_index;
    return mat_ans;
}
Matrix DMtrans(Matrix *tMat) // transpose matrix
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
Matrix DMmultiply(Matrix *s1Mat, Matrix *s2Mat) // matrix multiplication
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
Matrix DMaugment(Matrix *s1Mat, Matrix *s2Mat) // linking 2 source matrices by column
{
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
Matrix DMzeros(int dim) // generate & return an zero matrix
{
    int block_size = dim * dim;
    Matrix mat_ans;
    mat_ans.col = dim;
    mat_ans.row = dim;
    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (int i = 0; i < block_size; i++)
    {
        mat_ans.mat_index[i] = 0;
    }
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
Matrix DMidenti(int dim) // generate & return an identity matrix
{
    int block_size = dim * dim;
    Matrix mat_ans;
    mat_ans.col = dim;
    mat_ans.row = dim;
    mat_ans.mat_index = (Dtype *)malloc(sizeof(Dtype) * block_size);
    for (int i = 0; i < block_size; i++)
    {
        mat_ans.mat_index[i] = 0;
    }
    for (int i = 0; i <= dim; i++)
    {
        mat_ans.mat_index[(dim + 1) * i] = 1;
    }
    mem_usage += block_size * sizeof(Dtype);
    pList = DMadd_p(mat_ans.mat_index, pList);
    return mat_ans;
}
Dtype DMdet(Matrix *tMat) // return the determinant of the input matrix
{
    int block_size = tMat->col * tMat->row;
    if (tMat->col != tMat->row)
        return NAN;
    Matrix upper = DMref(tMat);
    det = fabs(det);
    for (int i = 0; i < block_size; i += 2)
    {
        if (tMat->mat_index[i] < 0)
            det = -det;
    }
    for (int i = 1; i < block_size; i += 2)
    {
        if (tMat->mat_index[i] > 0)
            det = -det;
    }
    return det;
}
void DMprint(Matrix *tMat) // a straightforward print function
{
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
int *rearrange(int *input, int arr_len) // rearrange the input value in ascending form, return the rearranged order
{
    int *data = (int *)malloc(sizeof(int) * arr_len);
    int *order = (int *)malloc(sizeof(int) * arr_len);
    for (int i = 0; i < arr_len; ++i)
    {
        data[i] = input[i];
    }
    int max = 0;
    int min = 0;
    for (int i = 0; i < arr_len; i++)
    {
        if (data[i] > max)
        {
            max = data[i];
        }
    }
    for (int k = 0; k < arr_len; k++)
    {
        int j = 0;
        for (int i = 0; i < arr_len; i++)
        {
            if (data[i] <= min)
            {
                min = data[i];
                j = i;
            }
        }
        data[j] = max + 1;
        order[k] = j;
        min = max;
    }
    free(data);
    return order;
}
void DMdeinit(memMgmt *heap) // free the allocated memory
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