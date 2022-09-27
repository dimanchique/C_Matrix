#include "Matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>

//#define DEBUG

static float **CreateMatrixData(int rows, int columns);
static void DeleteMatrixData(Matrix *m);

/** One int param **/
static Matrix *trimMatrixRow(Matrix *m, int row);
static void trimMatrixRow_OverrideOrigin(Matrix *m, int row);
static Matrix *trimMatrixColumn(Matrix *m, int column);
static void trimMatrixColumn_OverrideOrigin(Matrix *m, int column);

/** Two int params **/
static Matrix *trimMatrix(Matrix *m, int row, int column);
static void trimMatrix_OverrideOrigin(Matrix *m, int row, int column);
static Matrix *reshape(Matrix *m, int row, int column);
static void reshape_OverrideOrigin(Matrix *m, int row, int column);

/** One float param **/
static Matrix *addValue(Matrix *m, float Value);
static void addValue_OverrideOrigin(Matrix *m, float Value);
static Matrix *subtractValue(Matrix *m, float Value);
static void subtractValue_OverrideOrigin(Matrix *m, float Value);
static Matrix *multiplyByValue(Matrix *m, float Value);
static void multiplyByValue_OverrideOrigin(Matrix *m, float Value);
static Matrix *divideByValue(Matrix *m, float Value);
static void divideByValue_OverrideOrigin(Matrix *m, float Value);

/** No params **/
static void printFullMatrix(Matrix *m);
static int getNumOfRows(Matrix *m);
static int getNumOfColumns(Matrix *m);
static float determinant(Matrix *m);
static Matrix *copy(Matrix *m);
static Matrix *transpose(Matrix *m);
static void transpose_OverrideOrigin(Matrix *m);
static Matrix *inverse(Matrix *m);
static void inverse_OverrideOrigin(Matrix *m);

/** Matrix Operations: One matrix param **/
static Matrix *addMatrix(Matrix *m, Matrix *other_m);
static void addMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
static Matrix *subtractMatrix(Matrix *m, Matrix *other_m);
static void subtractMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
static Matrix *multiplyMatrix(Matrix *m, Matrix *other_m);
static void multiplyMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
static Matrix *divideMatrix(Matrix *m, Matrix *other_m);
static void divideMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);



Matrix *CreateMatrix(int rows, int columns) {
    /** Data **/
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->_rows = rows;
    matrix->_columns = columns;

    /** One int param **/
    matrix->TrimMatrixRow = trimMatrixRow;
    matrix->TrimMatrixRow_OverrideOrigin = trimMatrixRow_OverrideOrigin;
    matrix->TrimMatrixColumn = trimMatrixColumn;
    matrix->TrimMatrixColumn_OverrideOrigin = trimMatrixColumn_OverrideOrigin;

    /** Two int params **/
    matrix->TrimMatrix = trimMatrix;
    matrix->TrimMatrix_OverrideOrigin = trimMatrix_OverrideOrigin;
    matrix->Reshape = reshape;
    matrix->Reshape_OverrideOrigin = reshape_OverrideOrigin;

    /** One float param **/
    matrix->AddValue = addValue;
    matrix->AddValue_OverrideOrigin = addValue_OverrideOrigin;
    matrix->SubtractValue = subtractValue;
    matrix->SubtractValue_OverrideOrigin = subtractValue_OverrideOrigin;
    matrix->MultiplyByValue = multiplyByValue;
    matrix->MultiplyByValue_OverrideOrigin = multiplyByValue_OverrideOrigin;
    matrix->DivideByValue = divideByValue;
    matrix->DivideByValue_OverrideOrigin = divideByValue_OverrideOrigin;

    /** No params **/
    matrix->PrintFullMatrix = printFullMatrix;
    matrix->GetNumOfRows = getNumOfRows;
    matrix->GetNumOfColumns = getNumOfColumns;
    matrix->Determinant = determinant;
    matrix->Copy = copy;
    matrix->Transpose = transpose;
    matrix->Transpose_OverrideOrigin = transpose_OverrideOrigin;
    matrix->Inverse = inverse;
    matrix->Inverse_OverrideOrigin = inverse_OverrideOrigin;

    /** Matrix Operations: One matrix param **/
    matrix->AddMatrix = addMatrix;
    matrix->AddMatrix_OverrideOrigin = addMatrix_OverrideOrigin;
    matrix->SubtractMatrix = subtractMatrix;
    matrix->SubtractMatrix_OverrideOrigin = subtractMatrix_OverrideOrigin;
    matrix->MultiplyMatrix = multiplyMatrix;
    matrix->MultiplyMatrix_OverrideOrigin = multiplyMatrix_OverrideOrigin;
    matrix->DivideMatrix = divideMatrix;
    matrix->DivideMatrix_OverrideOrigin = divideMatrix_OverrideOrigin;



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

void DeleteMatrix(Matrix *m) {
    assert(m != NULL);
    DeleteMatrixData(m);
    free(m);
#ifdef DEBUG
    printf("Deleting Matrix with address: 0x%x\n", m);
#endif
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

static void DeleteMatrixData(Matrix *m) {
    assert(m != NULL);
#ifdef DEBUG
    printf("Deleting Matrix data with address: 0x%x\n", m);
#endif
    for (int i = 0; i < m->_rows; i++)
        free(m->_matrix[i]);
}

static Matrix *trimMatrixRow(Matrix *m, int row) {
    Matrix *temp = m->Copy(m);
    trimMatrixRow_OverrideOrigin(temp, row);
    return temp;
}

static void trimMatrixRow_OverrideOrigin(Matrix *m, int row) {
    assert(m != NULL);
    Matrix *temp = copy(m);
    if (!temp) return;
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

static Matrix *trimMatrixColumn(Matrix *m, int column) {
    Matrix *temp = m->Copy(m);
    trimMatrixColumn_OverrideOrigin(temp, column);
    return temp;
}

static void trimMatrixColumn_OverrideOrigin(Matrix *m, int column) {
    assert(m != NULL);
    Matrix *temp = copy(m);
    if (!temp) return;
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

static Matrix *trimMatrix(Matrix *m, int row, int column) {
    Matrix *temp = m->Copy(m);
    trimMatrix_OverrideOrigin(temp, row, column);
    return temp;
}

static void trimMatrix_OverrideOrigin(Matrix *m, int row, int column) {
    trimMatrixRow_OverrideOrigin(m, row);
    trimMatrixColumn_OverrideOrigin(m, column);
}

static Matrix *reshape(Matrix *m, int row, int column) {
    Matrix *temp = copy(m);
    if (!temp) return NULL;
    reshape_OverrideOrigin(temp, row, column);
    return temp;
}

static void reshape_OverrideOrigin(Matrix *m, int row, int column) {
    assert(m != NULL);
    assert(row*column == m->_rows * m->_columns);
    DeleteMatrixData(m);
    Matrix *temp = copy(m);
    if (!temp) return;
    float **matrix = CreateMatrixData(row, column);
    if (!matrix) return;
    int CurrentRow = 0;
    int CurrentColumn = 0;
    for (int i = 0; i < temp->_rows; i++) {
        for (int j = 0; j < temp->_columns; j++) {
            matrix[CurrentRow][CurrentColumn] = temp->_matrix[i][j];
            CurrentColumn++;
            if (CurrentColumn == column)
            {
                CurrentColumn = 0;
                CurrentRow++;
            }
        }
    }

    m->_matrix = matrix;
    m->_rows = row;
    m->_columns = column;
    DeleteMatrix(temp);
}

static Matrix *addValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    addValue_OverrideOrigin(temp, Value);
    return temp;
}

static void addValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] += Value;
}

static Matrix *subtractValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    subtractValue_OverrideOrigin(temp, Value);
    return temp;
}

static void subtractValue_OverrideOrigin(Matrix *m, float Value) {
    addValue_OverrideOrigin(m, -Value);
}

static Matrix *multiplyByValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    multiplyByValue_OverrideOrigin(temp, Value);
    return temp;
}

static void multiplyByValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] *= Value;
}

static Matrix *divideByValue(Matrix *m, float Value) {
    Matrix *temp = m->Copy(m);
    divideByValue_OverrideOrigin(temp, Value);
    return temp;
}

static void divideByValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    assert(Value != 0.0f);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] /= Value;
}

static void printFullMatrix(Matrix *m) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < m->_columns; j++)
            printf("%f ", m->_matrix[i][j]);
        printf("\n");
    }
}

static int getNumOfRows(Matrix *m) {
    assert(m != NULL);
    return m->_rows;
}

static int getNumOfColumns(Matrix *m) {
    assert(m != NULL);
    return m->_columns;
}

static float determinant(Matrix *m) {
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

static Matrix *copy(Matrix *m) {
    assert(m != NULL);
    Matrix *new_m = CreateMatrix(m->_rows, m->_columns);
    if (new_m == NULL)
        return NULL;
    for (int i = 0; i < m->_rows; i++)
        memcpy(new_m->_matrix[i], m->_matrix[i], m->_columns * sizeof(float));
    return new_m;
}

static Matrix *transpose(Matrix *m) {
    assert(m != NULL);
    Matrix *temp = copy(m);
    transpose_OverrideOrigin(temp);
    return temp;
}

static void transpose_OverrideOrigin(Matrix *m) {
    assert(m != NULL);
    float **new_m = CreateMatrixData(m->_columns, m->_rows);
    if (new_m == NULL) return;

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            new_m[j][i] = m->_matrix[i][j];
    DeleteMatrixData(m);
    m->_matrix = new_m;
    int temp = m->_rows;
    m->_rows = m->_columns;
    m->_columns = temp;
}

static Matrix *inverse(Matrix *m) {
    Matrix *temp = copy(m);
    inverse_OverrideOrigin(temp);
    return temp;
}

static void inverse_OverrideOrigin(Matrix *m) {
    assert(m != NULL);
    float det = determinant(m);

    if (fabsf(det) < 0.00005f) //epsilon
    {
        #ifdef DEBUG
        printf("Matrix with D = 0 can't be inversed");
        #endif
        return;
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

    transpose_OverrideOrigin(minor_m);
    divideByValue_OverrideOrigin(minor_m, det);

    for (int i = 0; i < m->_rows; i++)
        memcpy(m->_matrix[i], minor_m->_matrix[i], minor_m->_columns * sizeof(float));

    DeleteMatrix(minor_m);
    DeleteMatrix(temp);
}

static Matrix *addMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = m->Copy(m);
    addMatrix_OverrideOrigin(result, other_m);
    return result;
}

static void addMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] += other_m->_matrix[i][j];
}

static Matrix *subtractMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = m->Copy(m);
    subtractMatrix_OverrideOrigin(result, other_m);
    return result;
}

static void subtractMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] -= other_m->_matrix[i][j];
}

static Matrix *multiplyMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = copy(m);
    multiplyMatrix_OverrideOrigin(result, other_m);
    return result;
}

static void multiplyMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_columns == other_m->_rows);

    float **matrix = CreateMatrixData(m->_rows, other_m->_columns);
    if (!matrix) return;

    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < other_m->_columns; j++) {
            matrix[i][j] = 0;
            for (int k = 0; k < m->_columns; k++)
                matrix[i][j] += m->_matrix[i][k] * other_m->_matrix[k][j];
        }
    }
    DeleteMatrixData(m);
    m->_columns = other_m->_columns;
    m->_matrix = matrix;
}

static Matrix *divideMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = copy(m);
    divideMatrix_OverrideOrigin(result, other_m);
    return result;
}

static void divideMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    Matrix *temp = inverse(other_m);
    multiplyMatrix_OverrideOrigin(m, temp);
    DeleteMatrix(temp);
}
