#include <stdio.h>
#include "Matrix.h"

int main() {
    Matrix *m = CreateMatrix(3, 2);
    m->PrintFullMatrix(m);
    Matrix *nm = m->T(m);
    printf("Hello, World!\n");
    nm->PrintFullMatrix(nm);
    deleteMatrix(m);
    deleteMatrix(nm);
    return 0;
}
