#include "Matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>

//#define DEBUG

Matrix *CreateMatrix(int rows, int columns) {
    /** Data **/
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->_rows = rows;
    matrix->_columns = columns;
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

float **CreateMatrixData(int rows, int columns) {
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

void DeleteMatrixData(Matrix *m) {
    assert(m != NULL);
#ifdef DEBUG
    printf("Deleting Matrix data with address: 0x%x\n", m);
#endif
    for (int i = 0; i < m->_rows; i++)
        free(m->_matrix[i]);
}

Matrix *TrimMatrixRow(Matrix *m, int row) {
    Matrix *temp = Copy(m);
    TrimMatrixRow_OverrideOrigin(temp, row);
    return temp;
}

void TrimMatrixRow_OverrideOrigin(Matrix *m, int row) {
    assert(m != NULL);
    Matrix *temp = Copy(m);
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

Matrix *TrimMatrixColumn(Matrix *m, int column) {
    Matrix *temp = Copy(m);
    TrimMatrixColumn_OverrideOrigin(temp, column);
    return temp;
}

void TrimMatrixColumn_OverrideOrigin(Matrix *m, int column) {
    assert(m != NULL);
    Matrix *temp = Copy(m);
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

Matrix *TrimMatrix(Matrix *m, int row, int column) {
    Matrix *temp = Copy(m);
    TrimMatrix_OverrideOrigin(temp, row, column);
    return temp;
}

void TrimMatrix_OverrideOrigin(Matrix *m, int row, int column) {
    TrimMatrixRow_OverrideOrigin(m, row);
    TrimMatrixColumn_OverrideOrigin(m, column);
}

Matrix *Reshape(Matrix *m, int row, int column) {
    Matrix *temp = Copy(m);
    if (!temp) return NULL;
    Reshape_OverrideOrigin(temp, row, column);
    return temp;
}

void Reshape_OverrideOrigin(Matrix *m, int row, int column) {
    assert(m != NULL);
    assert(row*column == m->_rows * m->_columns);
    DeleteMatrixData(m);
    Matrix *temp = Copy(m);
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

Matrix *AddValue(Matrix *m, float Value) {
    Matrix *temp = Copy(m);
    AddValue_OverrideOrigin(temp, Value);
    return temp;
}

void AddValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] += Value;
}

Matrix *SubtractValue(Matrix *m, float Value) {
    Matrix *temp = Copy(m);
    SubtractValue_OverrideOrigin(temp, Value);
    return temp;
}

void SubtractValue_OverrideOrigin(Matrix *m, float Value) {
    AddValue_OverrideOrigin(m, -Value);
}

Matrix *MultiplyByValue(Matrix *m, float Value) {
    Matrix *temp = Copy(m);
    MultiplyByValue_OverrideOrigin(temp, Value);
    return temp;
}

void MultiplyByValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] *= Value;
}

Matrix *DivideByValue(Matrix *m, float Value) {
    Matrix *temp = Copy(m);
    DivideByValue_OverrideOrigin(temp, Value);
    return temp;
}

void DivideByValue_OverrideOrigin(Matrix *m, float Value) {
    assert(m != NULL);
    assert(Value != 0.0f);
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] /= Value;
}

void PrintFullMatrix(Matrix *m) {
    assert(m != NULL);
    for (int i = 0; i < m->_rows; i++) {
        for (int j = 0; j < m->_columns; j++)
            printf("%f ", m->_matrix[i][j]);
        printf("\n");
    }
}

int GetNumOfRows(Matrix *m) {
    assert(m != NULL);
    return m->_rows;
}

int GetNumOfColumns(Matrix *m) {
    assert(m != NULL);
    return m->_columns;
}

float Determinant(Matrix *m) {
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
        temp = TrimMatrix(m, 0, f);
        det += sign * m->_matrix[0][f] * Determinant(temp);
        sign = -sign;
    }
    DeleteMatrix(temp);
    return det;
}

Matrix *Copy(Matrix *m) {
    assert(m != NULL);
    Matrix *new_m = CreateMatrix(m->_rows, m->_columns);
    if (new_m == NULL)
        return NULL;
    for (int i = 0; i < m->_rows; i++)
        memcpy(new_m->_matrix[i], m->_matrix[i], m->_columns * sizeof(float));
    return new_m;
}

Matrix *Transpose(Matrix *m) {
    assert(m != NULL);
    Matrix *temp = Copy(m);
    Transpose_OverrideOrigin(temp);
    return temp;
}

void Transpose_OverrideOrigin(Matrix *m) {
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

Matrix *Inverse(Matrix *m) {
    Matrix *temp = Copy(m);
    Inverse_OverrideOrigin(temp);
    return temp;
}

void Inverse_OverrideOrigin(Matrix *m) {
    assert(m != NULL);
    float det = Determinant(m);

    if (fabsf(det) < 0.00005f) //epsilon
    {
        #ifdef DEBUG
        printf("Matrix with D = 0 can't be inversed");
        #endif
        return;
    }

    Matrix *minor_m = Copy(m);

    Matrix *temp;
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++) {
            temp = TrimMatrix(m, i, j);
            minor_m->_matrix[i][j] = Determinant(temp);
        }

    int sign = 1;
    for (int i = 0; i < minor_m->_rows; i++)
        for (int j = 0; j < minor_m->_columns; j++) {
            minor_m->_matrix[i][j] *= sign;
            sign *= -1;
        }

    Transpose_OverrideOrigin(minor_m);
    DivideByValue_OverrideOrigin(minor_m, det);

    for (int i = 0; i < m->_rows; i++)
        memcpy(m->_matrix[i], minor_m->_matrix[i], minor_m->_columns * sizeof(float));

    DeleteMatrix(minor_m);
    DeleteMatrix(temp);
}

Matrix *AddMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = Copy(m);
    AddMatrix_OverrideOrigin(result, other_m);
    return result;
}

void AddMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] += other_m->_matrix[i][j];
}

Matrix *SubtractMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = Copy(m);
    SubtractMatrix_OverrideOrigin(result, other_m);
    return result;
}

void SubtractMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    assert(m->_rows == other_m->_rows && m->_columns == other_m->_columns);

    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            m->_matrix[i][j] -= other_m->_matrix[i][j];
}

Matrix *MultiplyMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = Copy(m);
    MultiplyMatrix_OverrideOrigin(result, other_m);
    return result;
}

void MultiplyMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
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

Matrix *DivideMatrix(Matrix *m, Matrix *other_m) {
    Matrix *result = Copy(m);
    DivideMatrix_OverrideOrigin(result, other_m);
    return result;
}

void DivideMatrix_OverrideOrigin(Matrix *m, Matrix *other_m) {
    assert(m != NULL);
    assert(other_m != NULL);
    Matrix *temp = Inverse(other_m);
    MultiplyMatrix_OverrideOrigin(m, temp);
    DeleteMatrix(temp);
}

Matrix *ReplaceRow(struct Matrix *m, int row, float* new_row) {
    Matrix *result = Copy(m);
    ReplaceRow_OverrideOrigin(result, row, new_row);
    return result;
}

void ReplaceRow_OverrideOrigin(struct Matrix *m, int row, const float* new_row) {
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            if (i == row)
                m->_matrix[i][j] = new_row[i];
}

Matrix *ReplaceColumn(struct Matrix *m, int column, float* new_column) {
    Matrix *result = Copy(m);
    ReplaceColumn_OverrideOrigin(result, column, new_column);
    return result;
}

void ReplaceColumn_OverrideOrigin(struct Matrix *m, int column, const float* new_column) {
    for (int i = 0; i < m->_rows; i++)
        for (int j = 0; j < m->_columns; j++)
            if (j == column)
                m->_matrix[i][j] = new_column[i];
}
