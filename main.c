#include <stdio.h>
#include "Matrix.h"

int main() {
    Matrix *m = CreateMatrix(3, 3);
    m->_matrix[0][0] = 2;
    m->_matrix[0][1] = 5;
    m->_matrix[0][2] = 7;
    m->_matrix[1][0] = 6;
    m->_matrix[1][1] = 3;
    m->_matrix[1][2] = 4;
    m->_matrix[2][0] = 5;
    m->_matrix[2][1] = -2;
    m->_matrix[2][2] = -3;

    m->PrintFullMatrix(m);
    printf("\n");

    float a[] = {1.0f, 1.0f, 1.0f};
    m->ReplaceColumn_OverrideOrigin(m, 1, a);
    m->PrintFullMatrix(m);
    printf("\n");

    DeleteMatrix(m);
    return 0;
}
