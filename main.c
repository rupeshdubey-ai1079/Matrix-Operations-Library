#include "matrix.h"

int main() {
    printf("=== Matrix Operations Library ===\n");
    printf("    By: Rupesh Dubey\n\n");

    Matrix *A = createMatrix(3,3);
    Matrix *B = createMatrix(3,3);
    double a_data[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    double b_data[3][3] = {{9,8,7},{6,5,4},{3,2,1}};
    for (int i=0;i<3;i++) for (int j=0;j<3;j++) {
        A->data[i][j] = a_data[i][j];
        B->data[i][j] = b_data[i][j];
    }

    printMatrix(A, "Matrix A");
    printMatrix(B, "Matrix B");

    Matrix *sum  = addMatrix(A,B);    printMatrix(sum,  "A + B");
    Matrix *diff = subMatrix(A,B);    printMatrix(diff, "A - B");
    Matrix *prod = mulMatrix(A,B);    printMatrix(prod, "A * B");
    Matrix *tr   = transpose(A);      printMatrix(tr,   "Transpose of A");
    Matrix *I    = identity(3);       printMatrix(I,    "3x3 Identity");
    Matrix *s2   = scalarMul(A,2.0);  printMatrix(s2,   "A x 2 (scalar)");

    printf("\nDeterminant of A = %.4f\n", determinant(A));

    freeMatrix(A); freeMatrix(B); freeMatrix(sum);
    freeMatrix(diff); freeMatrix(prod); freeMatrix(tr);
    freeMatrix(I); freeMatrix(s2);

    benchmark(200);
    benchmark(500);
    return 0;
}