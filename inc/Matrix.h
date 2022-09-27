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

    /** Void Operations: One int param **/
    VoidOperationOneIntParam TrimMatrixByRow_NoRet;
    VoidOperationOneIntParam TrimMatrixByColumn_NoRet;

    /** Void Operations: Two int params **/
    VoidOperationTwoIntParams TrimMatrix_NoRet;

    /** Void Operations: One float param **/
    VoidOperationOneFloatParam AddValue_NoRet;
    VoidOperationOneFloatParam SubtractValue_NoRet;
    VoidOperationOneFloatParam MultiplyByValue_NoRet;
    VoidOperationOneFloatParam DivideByValue_NoRet;

    /** Void Operations: No params **/
    VoidOperationNoParams PrintFullMatrix;

    /** Int Operations: No params **/
    IntOperationNoParams GetNumOfRows;
    IntOperationNoParams GetNumOfColumns;

    /** Float Operations: No params **/
    FloatOperationNoParams Determinant;

    /** Matrix Operations: No params **/
    MatrixOperationNoParams T;
    MatrixOperationNoParams Copy;
    MatrixOperationNoParams Inverse;

    /** Matrix Operations: One matrix param **/
    MatrixOperationOneMatrixParam AddMatrix;
    MatrixOperationOneMatrixParam SubtractMatrix;
    MatrixOperationOneMatrixParam MultiplyMatrix;
    MatrixOperationOneMatrixParam DivideMatrix;

    /** Void Operations: One int param **/
    MatrixOperationOneIntParam TrimMatrixByRow;
    MatrixOperationOneIntParam TrimMatrixByColumn;

    /** Void Operations: Two int params **/
    MatrixOperationTwoIntParams TrimMatrix;

    /** Void Operations: One float param **/
    MatrixOperationOneFloatParam AddValue;
    MatrixOperationOneFloatParam SubtractValue;
    MatrixOperationOneFloatParam MultiplyByValue;
    MatrixOperationOneFloatParam DivideByValue;

} Matrix;

Matrix* CreateMatrix(int rows, int columns);
void DeleteMatrix(Matrix* m);
