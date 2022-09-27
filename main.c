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

    Matrix* matrix = m->Inverse(m);
    matrix->PrintFullMatrix(matrix);

    printf("\n");
    Matrix* mm = m->MultiplyMatrix(m, matrix);
    mm->PrintFullMatrix(mm);
    printf("\n");
    mm->Reshape_OverrideOrigin(mm, 1, 9);
    mm->PrintFullMatrix(mm);
    DeleteMatrix(mm);
    DeleteMatrix(m);
    DeleteMatrix(matrix);
    return 0;
}
