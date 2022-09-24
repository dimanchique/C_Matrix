#pragma once

struct Matrix;

typedef void (*VoidOperationZeroParams)(struct Matrix*);
typedef void (*VoidOperationOneFloatParam)(struct Matrix*, float);
typedef struct Matrix* (*ReturnMatrixOperation)(struct Matrix*);
typedef float (*ReturnFloatOperation)(struct Matrix*);
typedef int (*ReturnIntOperation)(struct Matrix*);

typedef struct Matrix {
    float **matrix;
    int _rows;
    int _columns;

    VoidOperationZeroParams PrintFullMatrix;
    VoidOperationZeroParams PrintNumOfRows;
    VoidOperationZeroParams PrintNumOfColumns;

    VoidOperationOneFloatParam AddValue;
    VoidOperationOneFloatParam SubtractValue;
    VoidOperationOneFloatParam MultiplyByValue;
    VoidOperationOneFloatParam DivideByValue;

    ReturnIntOperation GetNumOfRows;
    ReturnIntOperation GetNumOfColumns;
    ReturnFloatOperation Determinant;
    ReturnMatrixOperation T;
    ReturnMatrixOperation Copy;
} Matrix;

Matrix* CreateMatrix(int n, int m);
void DeleteMatrix(Matrix* m);
