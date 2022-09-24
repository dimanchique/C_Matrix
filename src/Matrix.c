#include "Matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

static Matrix* copy(Matrix* m);

static Matrix* transpose(Matrix* m);
static Matrix* inverse(Matrix* m);

static int getNumOfRows(Matrix* m);
static int getNumOfColumns(Matrix* m);

static void printNumOfRows(Matrix* m);
static void printNumOfColumns(Matrix* m);
static void printFullMatrix(Matrix* m);
static void addValue(Matrix* m, float Value);
static void subtractValue(Matrix* m, float Value);
static void multiplyByValue(Matrix* m, float Value);
static void divideByValue(Matrix* m, float Value);

static void addMatrix(Matrix* m, Matrix *other_m);
static void subtractMatrix(Matrix* m, Matrix *other_m);
static void multiplyMatrix(Matrix* m, Matrix *other_m);
static void divideMatrix(Matrix* m, Matrix *other_m);

static float determinant(Matrix* m);

Matrix* CreateMatrix(int n, int m) {
    Matrix* matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->_rows = n;
    matrix->_columns = m;

    matrix->PrintFullMatrix = printFullMatrix;
    matrix->PrintNumOfRows = printNumOfRows;
    matrix->PrintNumOfColumns = printNumOfColumns;

    matrix->AddValue = addValue;
    matrix->SubtractValue = subtractValue;
    matrix->MultiplyByValue = multiplyByValue;
    matrix->DivideByValue = divideByValue;

    matrix->GetNumOfRows = getNumOfRows;
    matrix->GetNumOfColumns = getNumOfColumns;
    matrix->Determinant = determinant;

    matrix->T = transpose;
    matrix->Copy = copy;

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

    printf("Created Matrix with address: 0x%x\n", matrix);
    return matrix;
}

Matrix* copy(Matrix* m) {
    assert(m != NULL);
    Matrix* new_m = CreateMatrix(m->_rows, m->_columns);
    if (new_m == NULL)
        return  NULL;
    for (int i = 0; i < m->_rows; i++)
        memcpy(new_m->matrix[i], m->matrix[i], m->_columns * sizeof(float));
    return new_m;
}

Matrix* transpose(Matrix* m) {
    assert(m != NULL);
    Matrix* new_m = CreateMatrix(m->_columns, m->_rows);
    if (new_m == NULL)
        return  NULL;

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            new_m->matrix[j][i] = m->matrix[i][j];
    return new_m;
}

void DeleteMatrix(Matrix* m) {
    assert(m != NULL);
    printf("Deleting Matrix with address: 0x%x\n", m);
    for (int i = 0; i < m->_rows; i++)
        free(m->matrix[i]);
    free(m);
}

void printNumOfRows(Matrix* m) {
    assert(m != NULL);
    printf("%d\n", m->_rows);
}

void printNumOfColumns(Matrix* m) {
    assert(m != NULL);
    printf("%d\n", m->_columns);
}

void printFullMatrix(Matrix* m) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < m->_columns; j++)
            printf("%f ", m->matrix[i][j]);
        printf("\n");
    }
}

int getNumOfRows(Matrix* m) {
    assert(m != NULL);
    return m->_rows;
}

int getNumOfColumns(Matrix* m) {
    assert(m != NULL);
    return m->_columns;
}

float determinant(Matrix* m) {
    assert(m != NULL);
    assert(m->_rows == m->_columns);

    if (m->_rows == 1)
        return m->matrix[0][0];
    if (m->_rows == 2)
        return m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0];

    //TODO: Add recursive calculations for more then 2x2 matrix

}

void addValue(Matrix* m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->matrix[i][j] += Value;
}

void subtractValue(Matrix* m, float Value) {
    addValue(m, -Value);
}

void multiplyByValue(Matrix* m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->matrix[i][j] *= Value;
}

void divideByValue(Matrix* m, float Value) {
    assert(Value != 0.0f);
    multiplyByValue(m, 1 / Value);
}

void addMatrix(Matrix* m, Matrix *other_m) {
    assert(m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->matrix[i][j] += other_m->matrix[i][j];
}


void subtractMatrix(Matrix* m, Matrix *other_m) {
    assert(m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->matrix[i][j] -= other_m->matrix[i][j];
}