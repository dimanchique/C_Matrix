#include "Matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

Matrix *CreateMatrix(int n, int m) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->_rows = n;
    matrix->_columns = m;

    matrix->PrintFullMatrix = printFullMatrix;
    matrix->PrintNumOfRows = printNumOfRows;
    matrix->PrintNumOfColumns = printNumOfColumns;
    matrix->Delete = deleteMatrix;

    matrix->GetNumOfRows = getNumOfRows;
    matrix->GetNumOfColumns = getNumOfColumns;
    matrix->Determinant = determinant;

    matrix->T = transpose;

    matrix->matrix = (float **) malloc(matrix->_rows * sizeof(float *));
    if (matrix == NULL) {
        printf("Out of memory during creating Matrix pointer");
        return NULL;
    }

    int FilledRows = 0;

    for (int i = 0; i < matrix->_rows; i++)
    {
        matrix->matrix[i] = (float *) malloc(matrix->_columns * sizeof(float));
        FilledRows++;
    }

    if (FilledRows < matrix->_rows)
    {
        printf("Out of memory during creating Matrix rows");
        for (int i = 0; i < FilledRows; i++)
            free(matrix->matrix[i]);
        free(matrix);
        matrix = NULL;
    }

    return matrix;
}

Matrix *transpose(Matrix *m) {
    assert(m != NULL);
    Matrix *new_m = CreateMatrix(m->_columns, m->_rows);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            new_m->matrix[j][i] = m->matrix[i][j];
    return new_m;
}

void deleteMatrix(Matrix *m) {
    assert(m != NULL);

    for (int i = 0; i < m->_rows; i++)
        free(m->matrix[i]);
    free(m);
}

void printNumOfRows(Matrix *m) {
    assert(m != NULL);
    printf("%d\n", m->_rows);
}

void printNumOfColumns(Matrix *m) {
    assert(m != NULL);
    printf("%d\n", m->_columns);
}

void printFullMatrix(Matrix *m) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < m->_columns; j++)
            printf("%f ", m->matrix[i][j]);
        printf("\n");
    }
}

int getNumOfRows(struct Matrix *m) {
    assert(m != NULL);
    return m->_rows;
}

int getNumOfColumns(struct Matrix *m) {
    assert(m != NULL);
    return m->_columns;
}

float determinant(struct Matrix *m) {
    assert(m != NULL);
    assert(m->_rows == m->_columns);

    if (m->_rows == 1)
        return m->matrix[0][0];
    if (m->_rows == 2)
        return m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0];

    //TODO: Add recursive calculations for more then 2x2 matrix

}
