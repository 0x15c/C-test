#include "Dmatrix.h"
#include "Dmatrix.c"
#include <stdio.h>
int main(void)
{
    memMgmt *heap = DMinit();
    Dtype test_mat[6][6] = {
        {3.2f, 2.0f, 4.0f, 8.0f,12.0f,12.5f},
        {4.0f, 0.0f, 1.0f, 0.5f,0.38f,0.78f},
        {1.0f, 2.5f, 4.5f, 12.0f,12.4f,8.2f},
        {1.0f, 2.7f, 9.3f, 0.8f,12.1f,0.9f},
        {0.7f,0.4f,0.2f,0.0f,1.0f,0.8f},
        {0.0f,1.0f,12.0f,15.6f,0.0f,12.2f},
    };
    Matrix test = {
        .row = 6,
        .col = 6,
        .mat_index = &test_mat[0][0],
    };
    Matrix id = DMIdenti(6);
    Matrix a = DMRef(&id);
    DMprint(&a);
    free_pList(heap);
    return 0;
}