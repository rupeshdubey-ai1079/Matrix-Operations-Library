#include "matrix.h"
#include <time.h>
#include <string.h>

Matrix* createMatrix(int rows, int cols) {
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows; m->cols = cols;
    m->data = malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
        m->data[i] = calloc(cols, sizeof(double));
    return m;
}

void freeMatrix(Matrix *m) {
    for (int i = 0; i < m->rows; i++) free(m->data[i]);
    free(m->data); free(m);
}

void printMatrix(const Matrix *m, const char *label) {
    printf("\n--- %s (%dx%d) ---\n", label, m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        printf("  |");
        for (int j = 0; j < m->cols; j++) printf(" %8.3f", m->data[i][j]);
        printf(" |\n");
    }
}

Matrix* addMatrix(const Matrix *a, const Matrix *b) {
    if (a->rows!=b->rows||a->cols!=b->cols) { printf("Dimension mismatch!\n"); return NULL; }
    Matrix *r = createMatrix(a->rows, a->cols);
    for (int i=0;i<a->rows;i++) for (int j=0;j<a->cols;j++)
        r->data[i][j] = a->data[i][j] + b->data[i][j];
    return r;
}

Matrix* subMatrix(const Matrix *a, const Matrix *b) {
    if (a->rows!=b->rows||a->cols!=b->cols) { printf("Dimension mismatch!\n"); return NULL; }
    Matrix *r = createMatrix(a->rows, a->cols);
    for (int i=0;i<a->rows;i++) for (int j=0;j<a->cols;j++)
        r->data[i][j] = a->data[i][j] - b->data[i][j];
    return r;
}

Matrix* mulMatrix(const Matrix *a, const Matrix *b) {
    if (a->cols!=b->rows) { printf("Incompatible dimensions!\n"); return NULL; }
    Matrix *r = createMatrix(a->rows, b->cols);
    for (int i=0;i<a->rows;i++)
        for (int j=0;j<b->cols;j++)
            for (int k=0;k<a->cols;k++)
                r->data[i][j] += a->data[i][k] * b->data[k][j];
    return r;
}

Matrix* transpose(const Matrix *m) {
    Matrix *r = createMatrix(m->cols, m->rows);
    for (int i=0;i<m->rows;i++) for (int j=0;j<m->cols;j++)
        r->data[j][i] = m->data[i][j];
    return r;
}

double determinant(const Matrix *m) {
    if (m->rows!=m->cols) { printf("Not a square matrix!\n"); return 0; }
    int n = m->rows;
    if (n==1) return m->data[0][0];
    if (n==2) return m->data[0][0]*m->data[1][1] - m->data[0][1]*m->data[1][0];
    double det = 0;
    Matrix *sub = createMatrix(n-1, n-1);
    for (int c=0;c<n;c++) {
        int ri=0;
        for (int i=1;i<n;i++) {
            int ci=0;
            for (int j=0;j<n;j++) { if (j==c) continue; sub->data[ri][ci++]=m->data[i][j]; }
            ri++;
        }
        det += (c%2==0?1:-1) * m->data[0][c] * determinant(sub);
    }
    freeMatrix(sub);
    return det;
}

Matrix* scalarMul(const Matrix *m, double scalar) {
    Matrix *r = createMatrix(m->rows, m->cols);
    for (int i=0;i<m->rows;i++) for (int j=0;j<m->cols;j++)
        r->data[i][j] = m->data[i][j] * scalar;
    return r;
}

Matrix* identity(int n) {
    Matrix *m = createMatrix(n, n);
    for (int i=0;i<n;i++) m->data[i][i] = 1.0;
    return m;
}

void benchmark(int size) {
    printf("\nBenchmark: %dx%d matrix multiplication...\n", size, size);
    Matrix *a = createMatrix(size,size);
    Matrix *b = createMatrix(size,size);
    for (int i=0;i<size;i++) for (int j=0;j<size;j++) {
        a->data[i][j] = (double)rand()/RAND_MAX;
        b->data[i][j] = (double)rand()/RAND_MAX;
    }
    clock_t start = clock();
    Matrix *c = mulMatrix(a, b);
    printf("  Time: %.4f seconds\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    freeMatrix(a); freeMatrix(b); freeMatrix(c);
}