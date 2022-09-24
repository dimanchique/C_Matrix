#include "Matrix.h"

int main() {
    Matrix *m = CreateMatrix(3, 2);
    m->PrintFullMatrix(m);
    Matrix *nm = m->Copy(m);
    nm->PrintFullMatrix(nm);
    DeleteMatrix(m);
    DeleteMatrix(nm);
    return 0;
}
