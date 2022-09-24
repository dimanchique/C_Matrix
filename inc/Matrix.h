#pragma once

struct Matrix;

typedef void (*VoidOperation)(struct Matrix *m);
typedef struct Matrix* (*ReturnMatrixOperation)(struct Matrix *m);
typedef float (*ReturnFloatOperation)(struct Matrix *m);
typedef int (*ReturnIntOperation)(struct Matrix *m);

typedef struct Matrix {
    float **matrix;
    int _rows;
    int _columns;

    VoidOperation PrintFullMatrix;
    VoidOperation PrintNumOfRows;
    VoidOperation PrintNumOfColumns;
    VoidOperation Delete;
    ReturnIntOperation GetNumOfRows;
    ReturnIntOperation GetNumOfColumns;
    ReturnFloatOperation Determinant;
    ReturnMatrixOperation T;
} Matrix;

Matrix *CreateMatrix(int n, int m);
Matrix *transpose(struct Matrix *m);
int getNumOfRows(struct Matrix *m);
int getNumOfColumns(struct Matrix *m);
void printNumOfRows(struct Matrix *m);
void printNumOfColumns(struct Matrix *m);
void printFullMatrix(struct Matrix *m);
void deleteMatrix(struct Matrix *m);
float determinant(struct Matrix *m);
