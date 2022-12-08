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

    PrintFullMatrix(m);
    printf("\n");

    float a[] = {1.0f, 1.0f, 1.0f};
    ReplaceColumn_OverrideOrigin(m, 1, a);
    ReplaceRow_OverrideOrigin(m, 1, a);
    PrintFullMatrix(m);
    printf("\n");

    float D = Determinant(m);
    printf("D = %f\n", D);

    DeleteMatrix(m);
    return 0;
}
