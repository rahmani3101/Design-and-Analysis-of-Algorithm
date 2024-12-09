//Write a program in C, to implement Strassen's matrix multiplication.

#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void addMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtractMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Function to multiply two matrices using Strassen's algorithm
void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int **A11 = (int **)malloc(newSize * sizeof(int *));
    int **A12 = (int **)malloc(newSize * sizeof(int *));
    int **A21 = (int **)malloc(newSize * sizeof(int *));
    int **A22 = (int **)malloc(newSize * sizeof(int *));
    int **B11 = (int **)malloc(newSize * sizeof(int *));
    int **B12 = (int **)malloc(newSize * sizeof(int *));
    int **B21 = (int **)malloc(newSize * sizeof(int *));
    int **B22 = (int **)malloc(newSize * sizeof(int *));
    int **M1 = (int **)malloc(newSize * sizeof(int *));
    int **M2 = (int **)malloc(newSize * sizeof(int *));
    int **M3 = (int **)malloc(newSize * sizeof(int *));
    int **M4 = (int **)malloc(newSize * sizeof(int *));
    int **M5 = (int **)malloc(newSize * sizeof(int *));
    int **M6 = (int **)malloc(newSize * sizeof(int *));
    int **M7 = (int **)malloc(newSize * sizeof(int *));
    int **AResult = (int **)malloc(newSize * sizeof(int *));
    int **BResult = (int **)malloc(newSize * sizeof(int *));

    for (int i = 0; i < newSize; i++) {
        A11[i] = (int *)malloc(newSize * sizeof(int));
        A12[i] = (int *)malloc(newSize * sizeof(int));
        A21[i] = (int *)malloc(newSize * sizeof(int));
        A22[i] = (int *)malloc(newSize * sizeof(int));
        B11[i] = (int *)malloc(newSize * sizeof(int));
        B12[i] = (int *)malloc(newSize * sizeof(int));
        B21[i] = (int *)malloc(newSize * sizeof(int));
        B22[i] = (int *)malloc(newSize * sizeof(int));
        M1[i] = (int *)malloc(newSize * sizeof(int));
        M2[i] = (int *)malloc(newSize * sizeof(int));
        M3[i] = (int *)malloc(newSize * sizeof(int));
        M4[i] = (int *)malloc(newSize * sizeof(int));
        M5[i] = (int *)malloc(newSize * sizeof(int));
        M6[i] = (int *)malloc(newSize * sizeof(int));
        M7[i] = (int *)malloc(newSize * sizeof(int));
        AResult[i] = (int *)malloc(newSize * sizeof(int));
        BResult[i] = (int *)malloc(newSize * sizeof(int));
    }

    // Dividing matrices A and B into sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    addMatrices(A11, A22, AResult, newSize);
    addMatrices(B11, B22, BResult, newSize);
    strassen(AResult, BResult, M1, newSize);

    // M2 = (A21 + A22) * B11
    addMatrices(A21, A22, AResult, newSize);
    strassen(AResult, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    subtractMatrices(B12, B22, BResult, newSize);
    strassen(A11, BResult, M3, newSize);

    // M4 = A22 * (B21 - B11)
    subtractMatrices(B21, B11, BResult, newSize);
    strassen(A22, BResult, M4, newSize);

    // M5 = (A11 + A12) * B22
    addMatrices(A11, A12, AResult, newSize);
    strassen(AResult, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    subtractMatrices(A21, A11, AResult, newSize);
    addMatrices(B11, B12, BResult, newSize);
    strassen(AResult, BResult, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    subtractMatrices(A12, A22, AResult, newSize);
    addMatrices(B21, B22, BResult, newSize);
    strassen(AResult, BResult, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    addMatrices(M1, M4, AResult, newSize);
    subtractMatrices(AResult, M5, AResult, newSize);
    addMatrices(AResult, M7, C, newSize);

    // C12 = M3 + M5
    addMatrices(M3, M5, C + 0 * newSize, newSize);

    // C21 = M2 + M4
    addMatrices(M2, M4, C + newSize * 0, newSize);

    // C22 = M1 - M2 + M3 + M6
    addMatrices(M1, M2, AResult, newSize);
    subtractMatrices(AResult, M3, AResult, newSize);
    addMatrices(AResult, M6, C + newSize * newSize, newSize);

    // Free dynamically allocated memory for sub-matrices
    for (int i = 0; i < newSize; i++) {
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);
        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);
        free(M1[i]);
        free(M2[i]);
        free(M3[i]);
        free(M4[i]);
        free(M5[i]);
        free(M6[i]);
        free(M7[i]);
        free(AResult[i]);
        free(BResult[i]);
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);
    free(B11);
    free(B12);
    free(B21);
    free(B22);
    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);
    free(AResult);
    free(BResult);
}

// Function to print the matrix
void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; // Size of the matrix
    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    // Example matrices
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3; A[0][3] = 4;
    A[1][0] = 5; A[1][1] = 6; A[1][2] = 7; A[1][3] = 8;
    A[2][0] = 9; A[2][1] = 10; A[2][2] = 11; A[2][3] = 12;
    A[3][0] = 13; A[3][1] = 14; A[3][2] = 15; A[3][3] = 16;

    B[0][0] = 1; B[0][1] = 0; B[0][2] = 0; B[0][3] = 0;
    B[1][0] = 0; B[1][1] = 1; B[1][2] = 0; B[1][3] = 0;
    B[2][0] = 0; B[2][1] = 0; B[2][2] = 1; B[2][3] = 0;
    B[3][0] = 0; B[3][1] = 0; B[3][2] = 0; B[3][3] = 1;

    // Perform Strassen's matrix multiplication
    strassen(A, B, C, n);

    // Print result
    printf("Result of A * B is:\n");
    printMatrix(C, n);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
