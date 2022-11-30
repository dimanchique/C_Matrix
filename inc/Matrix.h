#pragma once
struct Matrix;

typedef struct Matrix {
    float **_matrix;
    int _rows;
    int _columns;
} Matrix;

Matrix* CreateMatrix(int rows, int columns);
void DeleteMatrix(Matrix* m);

float **CreateMatrixData(int rows, int columns);
void DeleteMatrixData(Matrix *m);

/** One int param **/
Matrix *TrimMatrixRow(Matrix *m, int row);
void TrimMatrixRow_OverrideOrigin(Matrix *m, int row);
Matrix *TrimMatrixColumn(Matrix *m, int column);
void TrimMatrixColumn_OverrideOrigin(Matrix *m, int column);

/** One int param, one float array **/
Matrix *ReplaceRow(struct Matrix *m, int row, float* new_row);
void ReplaceRow_OverrideOrigin(struct Matrix *m, int row, const float* new_row);
Matrix *ReplaceColumn(struct Matrix *m, int column, float* new_column);
void ReplaceColumn_OverrideOrigin(struct Matrix *m, int column, const float* new_column);

/** Two int params **/
Matrix *TrimMatrix(Matrix *m, int row, int column);
void TrimMatrix_OverrideOrigin(Matrix *m, int row, int column);
Matrix *Reshape(Matrix *m, int row, int column);
void Reshape_OverrideOrigin(Matrix *m, int row, int column);

/** One float param **/
Matrix *AddValue(Matrix *m, float Value);
void AddValue_OverrideOrigin(Matrix *m, float Value);
Matrix *SubtractValue(Matrix *m, float Value);
void SubtractValue_OverrideOrigin(Matrix *m, float Value);
Matrix *MultiplyByValue(Matrix *m, float Value);
void MultiplyByValue_OverrideOrigin(Matrix *m, float Value);
Matrix *DivideByValue(Matrix *m, float Value);
void DivideByValue_OverrideOrigin(Matrix *m, float Value);

/** No params **/
void PrintFullMatrix(Matrix *m);
int GetNumOfRows(Matrix *m);
int GetNumOfColumns(Matrix *m);
float Determinant(Matrix *m);
Matrix *Copy(Matrix *m);
Matrix *Transpose(Matrix *m);
void Transpose_OverrideOrigin(Matrix *m);
Matrix *Inverse(Matrix *m);
void Inverse_OverrideOrigin(Matrix *m);

Matrix *AddMatrix(Matrix *m, Matrix *other_m);
void AddMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
Matrix *SubtractMatrix(Matrix *m, Matrix *other_m);
void SubtractMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
Matrix *MultiplyMatrix(Matrix *m, Matrix *other_m);
void MultiplyMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
Matrix *DivideMatrix(Matrix *m, Matrix *other_m);
void DivideMatrix_OverrideOrigin(Matrix *m, Matrix *other_m);
