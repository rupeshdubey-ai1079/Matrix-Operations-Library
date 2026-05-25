#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int    rows, cols;
    double **data;
} Matrix;

Matrix* createMatrix(int rows, int cols);
void    freeMatrix(Matrix *m);
void    printMatrix(const Matrix *m, const char *label);
Matrix* addMatrix(const Matrix *a, const Matrix *b);
Matrix* subMatrix(const Matrix *a, const Matrix *b);
Matrix* mulMatrix(const Matrix *a, const Matrix *b);
Matrix* transpose(const Matrix *m);
double  determinant(const Matrix *m);
Matrix* scalarMul(const Matrix *m, double scalar);
Matrix* identity(int n);
void    benchmark(int size);

#endif