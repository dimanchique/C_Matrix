#pragma once
struct Matrix;

/** No Return Functions **/
typedef void (*VoidOperationNoParams)(struct Matrix*);
typedef void (*VoidOperationOneMatrixParam)(struct Matrix*, struct Matrix*);
typedef void (*VoidOperationOneFloatParam)(struct Matrix*, float);
typedef void (*VoidOperationOneIntParam)(struct Matrix*, int);
typedef void (*VoidOperationTwoIntParams)(struct Matrix*, int, int);
/** Return Matrix Functions **/
typedef struct Matrix* (*MatrixOperationNoParams)(struct Matrix*);
typedef struct Matrix* (*MatrixOperationOneMatrixParam)(struct Matrix*, struct Matrix*);
typedef struct Matrix* (*MatrixOperationOneFloatParam)(struct Matrix*, float);
typedef struct Matrix* (*MatrixOperationOneIntParam)(struct Matrix*, int);
typedef struct Matrix* (*MatrixOperationTwoIntParams)(struct Matrix*, int, int);
/** Return Int/Float Functions **/
typedef float (*FloatOperationNoParams)(struct Matrix*);
typedef int (*IntOperationNoParams)(struct Matrix*);

typedef struct Matrix {
    /** Data **/
    float **_matrix;
    int _rows;
    int _columns;

    /** One int param **/
    MatrixOperationOneIntParam TrimMatrixRow;
    VoidOperationOneIntParam TrimMatrixRow_OverrideOrigin;
    MatrixOperationOneIntParam TrimMatrixColumn;
    VoidOperationOneIntParam TrimMatrixColumn_OverrideOrigin;

    /** Two int params **/
    MatrixOperationTwoIntParams TrimMatrix;
    VoidOperationTwoIntParams TrimMatrix_OverrideOrigin;
    MatrixOperationTwoIntParams Reshape;
    VoidOperationTwoIntParams Reshape_OverrideOrigin;

    /** One float param **/
    MatrixOperationOneFloatParam AddValue;
    VoidOperationOneFloatParam AddValue_OverrideOrigin;
    MatrixOperationOneFloatParam SubtractValue;
    VoidOperationOneFloatParam SubtractValue_OverrideOrigin;
    MatrixOperationOneFloatParam MultiplyByValue;
    VoidOperationOneFloatParam MultiplyByValue_OverrideOrigin;
    MatrixOperationOneFloatParam DivideByValue;
    VoidOperationOneFloatParam DivideByValue_OverrideOrigin;

    /** No params **/
    VoidOperationNoParams PrintFullMatrix;
    IntOperationNoParams GetNumOfRows;
    IntOperationNoParams GetNumOfColumns;
    FloatOperationNoParams Determinant;
    MatrixOperationNoParams Copy;
    MatrixOperationNoParams Transpose;
    VoidOperationNoParams Transpose_OverrideOrigin;
    MatrixOperationNoParams Inverse;
    VoidOperationNoParams Inverse_OverrideOrigin;

    /** Matrix Operations: One matrix param **/
    MatrixOperationOneMatrixParam AddMatrix;
    VoidOperationOneMatrixParam AddMatrix_OverrideOrigin;
    MatrixOperationOneMatrixParam SubtractMatrix;
    VoidOperationOneMatrixParam SubtractMatrix_OverrideOrigin;
    MatrixOperationOneMatrixParam MultiplyMatrix;
    VoidOperationOneMatrixParam MultiplyMatrix_OverrideOrigin;
    MatrixOperationOneMatrixParam DivideMatrix;
    VoidOperationOneMatrixParam DivideMatrix_OverrideOrigin;
} Matrix;

Matrix* CreateMatrix(int rows, int columns);
void DeleteMatrix(Matrix* m);
