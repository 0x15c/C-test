#include "Dmatrix.h"
#include "Dmatrix.c"
#include <stdio.h>
int main(void)
{
    memMgmt *heap = DMinit();
    Dtype test_mat[6][7] = {
        {1.0f, 2.0f, 4.0f, 8.0f,12.0f,12.5f,13.0f},
        {0.0f, 0.0f, 1.0f, 0.0625f,0.38f,0.78f,0.12f},
        {1.0f, 2.5f, 4.5f, 12.0f,12.4f,8.2f,3.75f},
        {1.0f, 2.7f, 9.3f, 0.8f,12.1f,0.0f,0.27f},
        {0.0f,0.0f,0.0f,0.0f,1.0f,0.8f,1.2f},
        {0.0f,1.0f,12.0f,15.6f,0.0f,12.2f,0.98f},
    };
    Matrix test = {
        .row = 6,
        .col = 7,
        .mat_index = &test_mat[0][0],
    };
    Matrix a = DMRef(&test);
    DMprint(&a);
    free_pList(heap);
    return 0;
}