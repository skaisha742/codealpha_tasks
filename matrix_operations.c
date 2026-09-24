
#include <stdio.h>

#define MAX 10

// Function to input a matrix
void inputMatrix(int matrix[MAX][MAX], int rows, int cols) {
    int i, j;

    printf("Enter elements of the matrix:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display a matrix
void displayMatrix(int matrix[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function for matrix addition
void addMatrices(int A[MAX][MAX], int B[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function for matrix multiplication
void multiplyMatrices(int A[MAX][MAX], int B[MAX][MAX],
                       int result[MAX][MAX],
                       int r1, int c1, int r2, int c2) {
    int i, j, k;

    // Initialize result matrix
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }

    // Matrix multiplication
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            for (k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function for matrix transpose
void transposeMatrix(int matrix[MAX][MAX],
                     int transpose[MAX][MAX],
                     int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
}

int main() {

    int choice;
    int A[MAX][MAX], B[MAX][MAX], result[MAX][MAX];
    int transpose[MAX][MAX];

    int rows, cols;
    int r1, c1, r2, c2;

    printf("=====================================\n");
    printf("       MATRIX OPERATIONS PROGRAM\n");
    printf("=====================================\n");

    printf("\nChoose an operation:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {

        // MATRIX ADDITION
        case 1:

            printf("\nEnter number of rows: ");
            scanf("%d", &rows);

            printf("Enter number of columns: ");
            scanf("%d", &cols);

            if (rows > MAX || cols > MAX || rows <= 0 || cols <= 0) {
                printf("Invalid matrix size!\n");
                return 0;
            }

            printf("\nEnter elements of Matrix A:\n");
            inputMatrix(A, rows, cols);

            printf("\nEnter elements of Matrix B:\n");
            inputMatrix(B, rows, cols);

            addMatrices(A, B, result, rows, cols);

            printf("\nMatrix A:\n");
            displayMatrix(A, rows, cols);

            printf("\nMatrix B:\n");
            displayMatrix(B, rows, cols);

            printf("\nResult of Matrix Addition:\n");
            displayMatrix(result, rows, cols);

            break;


        // MATRIX MULTIPLICATION
        case 2:

            printf("\nEnter rows of Matrix A: ");
            scanf("%d", &r1);

            printf("Enter columns of Matrix A: ");
            scanf("%d", &c1);

            printf("Enter rows of Matrix B: ");
            scanf("%d", &r2);

            printf("Enter columns of Matrix B: ");
            scanf("%d", &c2);

            if (r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0 ||
                r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX) {

                printf("Invalid matrix size!\n");
                return 0;
            }

            if (c1 != r2) {
                printf("\nMatrix multiplication is not possible.\n");
                printf("Columns of Matrix A must equal rows of Matrix B.\n");
                return 0;
            }

            printf("\nEnter elements of Matrix A:\n");
            inputMatrix(A, r1, c1);

            printf("\nEnter elements of Matrix B:\n");
            inputMatrix(B, r2, c2);

            multiplyMatrices(A, B, result, r1, c1, r2, c2);

            printf("\nMatrix A:\n");
            displayMatrix(A, r1, c1);

            printf("\nMatrix B:\n");
            displayMatrix(B, r2, c2);

            printf("\nResult of Matrix Multiplication:\n");
            displayMatrix(result, r1, c2);

            break;


        // MATRIX TRANSPOSE
        case 3:

            printf("\nEnter number of rows: ");
            scanf("%d", &rows);

            printf("Enter number of columns: ");
            scanf("%d", &cols);

            if (rows <= 0 || cols <= 0 || rows > MAX || cols > MAX) {
                printf("Invalid matrix size!\n");
                return 0;
            }

            printf("\nEnter elements of the matrix:\n");
            inputMatrix(A, rows, cols);

            transposeMatrix(A, transpose, rows, cols);

            printf("\nOriginal Matrix:\n");
            displayMatrix(A, rows, cols);

            printf("\nTranspose of Matrix:\n");
            displayMatrix(transpose, cols, rows);

            break;


        default:
            printf("\nInvalid choice!\n");
    }

    return 0;
}
