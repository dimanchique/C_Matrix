#include "Matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>

//#define DEBUG

static float **CreateMatrixData(int rows, int columns);
static void DeleteMatrixData(Matrix *m);

/** Void Operations: One int param **/
static void trimMatrixRow_OverrideOrigin(Matrix *m, int row);
static void trimMatrixColumn_OverrideOrigin(Matrix *m, int column);

/** Void Operations: Two int params **/
static void trimMatrix_OverrideOrigin(Matrix *m, int row, int column);

/** Void Operations: One float param **/
static void addValue_OverrideOrigin(Matrix *m, float Value);
static void subtractValue_OverrideOrigin(Matrix *m, float Value);
static void multiplyByValue_OverrideOrigin(Matrix *m, float Value);
static void divideByValue_OverrideOrigin(Matrix *m, float Value);

/** Void Operations: No params **/
static void printFullMatrix(Matrix *m);

/** Int Operations: No params **/
static int getNumOfRows(Matrix *m);
static int getNumOfColumns(Matrix *m);

/** Float Operations: No params **/
static float determinant(Matrix *m);

/** Matrix Operations: No params **/
static Matrix *copy(Matrix *m);
static Matrix *transpose(Matrix *m);
static Matrix *inverse(Matrix *m);

/** Matrix Operations: One matrix param **/
static Matrix *addMatrix(Matrix *m, Matrix *other_m);
static Matrix *subtractMatrix(Matrix *m, Matrix *other_m);
static Matrix *multiplyMatrix(Matrix *m, Matrix *other_m);
static Matrix *divideMatrix(Matrix *m, Matrix *other_m);

/** Void Operations: One int param **/
static Matrix *trimMatrixRow(Matrix *m, int row);
static Matrix *trimMatrixColumn(Matrix *m, int column);

/** Void Operations: Two int params **/
static Matrix *trimMatrix(Matrix *m, int row, int column);

/** Void Operations: One float param **/
static Matrix *addValue(Matrix *m, float Value);
static Matrix *subtractValue(Matrix *m, float Value);
static Matrix *multiplyByValue(Matrix *m, float Value);
static Matrix *divideByValue(Matrix *m, float Value);



Matrix *CreateMatrix(int rows, int columns) {
    /** Data **/
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->_rows = rows;
    matrix->_columns = columns;

    /** Void Operations: One int param **/
    matrix->TrimMatrixByRow_OverrideOrigin = trimMatrixRow_OverrideOrigin;
    matrix->TrimMatrixByColumn_OverrideOrigin = trimMatrixColumn_OverrideOrigin;

    /** Void Operations: Two int params **/
    matrix->TrimMatrix_OverrideOrigin = trimMatrix_OverrideOrigin;

    /** Void Operations: One float param **/
    matrix->AddValue_OverrideOrigin = addValue_OverrideOrigin;
    matrix->SubtractValue_OverrideOrigin = subtractValue_OverrideOrigin;
    matrix->MultiplyByValue_OverrideOrigin = multiplyByValue_OverrideOrigin;
    matrix->DivideByValue_OverrideOrigin = divideByValue_OverrideOrigin;

    /** Void Operations: No params **/
    matrix->PrintFullMatrix = printFullMatrix;

    /** Int Operations: No params **/
    matrix->GetNumOfRows = getNumOfRows;
    matrix->GetNumOfColumns = getNumOfColumns;

    /** Float Operations: No params **/
    matrix->Determinant = determinant;

    /** Matrix Operations: No params **/
    matrix->T = transpose;
    matrix->Copy = copy;
    matrix->Inverse = inverse;

    /** Matrix Operations: One matrix param **/
    matrix->AddMatrix = addMatrix;
    matrix->SubtractMatrix = subtractMatrix;
    matrix->MultiplyMatrix = multiplyMatrix;
    matrix->DivideMatrix = divideMatrix;

    /** Void Operations: One int param **/
    matrix->TrimMatrixByRow = trimMatrixRow;
    matrix->TrimMatrixByColumn = trimMatrixColumn;

    /** Void Operations: Two int params **/
    matrix->TrimMatrix = trimMatrix;

    /** Void Operations: One float param **/
    matrix->AddValue = addValue;
    matrix->SubtractValue = subtractValue;
    matrix->MultiplyByValue = multiplyByValue;
    matrix->DivideByValue = divideByValue;



    /** Initialize process **/
    matrix->_matrix = CreateMatrixData(rows, columns);

    if (matrix->_matrix) {
        #ifdef DEBUG
        printf("Created Matrix with address: 0x%x\n", matrix);
        #endif
        return matrix;
    }
    #ifdef DEBUG
    printf("Error while creating Matrix");
    #endif
    return NULL;
}

static float **CreateMatrixData(int rows, int columns) {
    float **matrix_data = NULL;
    matrix_data = (float **) malloc(rows * sizeof(float *));
    if (matrix_data == NULL) {
        #ifdef DEBUG
        printf("Out of memory during creating Matrix pointer");
        #endif
        return NULL;
    }

    int FilledRows = 0;
    for (int i = 0; i < rows; i++) {
        matrix_data[i] = (float *) malloc(columns * sizeof(float));
        FilledRows++;
    }

    if (FilledRows < rows) {
        #ifdef DEBUG
        printf("Out of memory during creating Matrix rows");
        #endif
        for (int i = 0; i < FilledRows; i++)
            free(matrix_data[i]);
        return NULL;
    }
    return matrix_data;
}

Matrix *copy(Matrix *m) {
    assert(m != NULL);
    Matrix *new_m = CreateMatrix(m->_rows, m->_columns);
    if (new_m == NULL)
        return NULL;
    for (int i = 0; i < m->_rows; i++)
        memcpy(new_m->_matrix[i], m->_matrix[i], m->_columns * sizeof(float));
    return new_m;
}

Matrix *transpose(Matrix *m) {
    assert(m != NULL);
    Matrix *new_m = CreateMatrix(m->_columns, m->_rows);
    if (new_m == NULL)
        return NULL;

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            new_m->_matrix[j][i] = m->_matrix[i][j];
    return new_m;
}

void DeleteMatrix(Matrix *m) {
    assert(m != NULL);
    DeleteMatrixData(m);
    free(m);
    #ifdef DEBUG
    printf("Deleting Matrix with address: 0x%x\n", m);
    #endif
}

static void DeleteMatrixData(Matrix *m) {
    assert(m != NULL);
    #ifdef DEBUG
    printf("Deleting Matrix data with address: 0x%x\n", m);
    #endif
    for (int i = 0; i < m->_rows; i++)
        free(m->_matrix[i]);
}

void printFullMatrix(Matrix *m) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < m->_columns; j++)
            printf("%f ", m->_matrix[i][j]);
        printf("\n");
    }
}

int getNumOfRows(Matrix *m) {
    assert(m != NULL);
    return m->_rows;
}

int getNumOfColumns(Matrix *m) {
    assert(m != NULL);
    return m->_columns;
}

float determinant(Matrix *m) {
    assert(m != NULL);
    assert(m->_rows == m->_columns);

    if (m->_rows == 1)
        return m->_matrix[0][0];
    if (m->_rows == 2)
        return m->_matrix[0][0] * m->_matrix[1][1] - m->_matrix[0][1] * m->_matrix[1][0];

    float det = 0;
    int sign = 1;
    Matrix *temp;
    for (int f = 0; f < m->_rows; f++) {
        temp = trimMatrix(m, 0, f);
        det += sign * m->_matrix[0][f] * determinant(temp);
        sign = -sign;
    }
    DeleteMatrix(temp);
    return det;
}

void addValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] += Value;
}

Matrix *addValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    addValue_OverrideOrigin(temp, Value);
    return temp;
}

void subtractValue_OverrideOrigin(Matrix *m, float Value) {
    addValue_OverrideOrigin(m, -Value);
}

Matrix *subtractValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    subtractValue_OverrideOrigin(temp, Value);
    return temp;
}

void multiplyByValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] *= Value;
}

Matrix *multiplyByValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    multiplyByValue_OverrideOrigin(temp, Value);
    return temp;
}

void divideByValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    assert(Value != 0.0f);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] /= Value;
}

Matrix *divideByValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    divideByValue_OverrideOrigin(temp, Value);
    return temp;
}

Matrix *addMatrix(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);

    Matrix *result = m->Copy(m);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            result->_matrix[i][j] += other_m->_matrix[i][j];

    return result;
}

Matrix *subtractMatrix(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);

    Matrix *result = m->Copy(m);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            result->_matrix[i][j] -= other_m->_matrix[i][j];

    return result;
}

Matrix *multiplyMatrix(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_columns == other_m->_rows);

    Matrix *result = CreateMatrix(m->_rows, other_m->_columns);

    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < other_m->_columns; j++) {
            result->_matrix[i][j] = 0;
            for (int k = 0; k < m->_columns; k++)
                result->_matrix[i][j] += m->_matrix[i][k] * other_m->_matrix[k][j];
        }
    }
    return result;
}

Matrix *divideMatrix(Matrix *m, Matrix *other_m) {
    Matrix *temp = inverse(other_m);
    Matrix *result = multiplyMatrix(m, temp);
    DeleteMatrix(temp);
    return result;
}

static void trimMatrixRow_OverrideOrigin(Matrix *m, int row) {
    Matrix *temp = copy(m);
    DeleteMatrixData(m);
    m->_rows--;
    m->_matrix = CreateMatrixData(m->_rows, m->_columns);
    if (m->_matrix == NULL) return;

    int CurrentRow = 0;
    for (int i = 0; i < temp->_rows; i++) {
        if (i == row) continue;
        for (int j = 0; j < temp->_columns; j++)
            m->_matrix[CurrentRow][j] = temp->_matrix[i][j];
        CurrentRow++;
    }
    DeleteMatrix(temp);
}

Matrix *trimMatrixRow(Matrix *m, int row) {
    Matrix *temp = m->Copy(m);
    trimMatrixRow_OverrideOrigin(temp, row);
    return temp;
}

static void trimMatrixColumn_OverrideOrigin(Matrix *m, int column) {
    Matrix *temp = copy(m);
    DeleteMatrixData(m);
    m->_columns--;
    m->_matrix = CreateMatrixData(m->_rows, m->_columns);
    if (m->_matrix == NULL) return;

    for (int i = 0; i < temp->_rows; i++) {
        int CurrentColumn = 0;
        for (int j = 0; j < temp->_columns; j++) {
            if (j == column) continue;
            m->_matrix[i][CurrentColumn] = temp->_matrix[i][j];
            CurrentColumn++;
        }
    }
    DeleteMatrix(temp);
}

Matrix *trimMatrixColumn(Matrix *m, int column) {
    Matrix *temp = m->Copy(m);
    trimMatrixColumn_OverrideOrigin(temp, column);
    return temp;
}

static void trimMatrix_OverrideOrigin(Matrix *m, int row, int column) {
    trimMatrixRow_OverrideOrigin(m, row);
    trimMatrixColumn_OverrideOrigin(m, column);
}

Matrix *trimMatrix(Matrix *m, int row, int column) {
    Matrix *temp = m->Copy(m);
    trimMatrix_OverrideOrigin(temp, row, column);
    return temp;
}

static Matrix *inverse(Matrix *m) {
    float det = determinant(m);

    if (fabsf(det) < 0.00005f) //epsilon
    {
        #ifdef DEBUG
        printf("Matrix with D = 0 can't be inversed");
        #endif
        return NULL;
    }

    Matrix *minor_m = m->Copy(m);

    Matrix *temp;
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++) {
            temp = m->TrimMatrix(m, i, j);
            minor_m->_matrix[i][j] = determinant(temp);
        }

    int sign = 1;
    for (int i = 0; i < minor_m->_rows; i++)
        for (int j = 0; j < minor_m->_columns; j++) {
            minor_m->_matrix[i][j] *= sign;
            sign *= -1;
        }

    Matrix *matrix = minor_m->T(minor_m);
    matrix->DivideByValue_OverrideOrigin(matrix, det);

    DeleteMatrix(minor_m);
    DeleteMatrix(temp);

    return matrix;
}