#include <stdio.h>

#define N 10
int blockSize = N / 2;
int A[N][N];
int B[N][N];
int C[N][N];

void print_matrix(int matrix[][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main (int argc, char *argv[]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
            B[i][j] = 2;
            C[i][j] = 0;
        }
    }

    print_matrix(A);
    print_matrix(B);

    // iterate over blocks
    for (int bi = 0; bi < N; bi += blockSize) {             // fix block row
        for (int bj = 0; bj < N; bj += blockSize) {         // fix block col
            for (int bk = 0; bk < N; bk += blockSize) {     // iterate over fixed block row/col
                // iterate inside the block
                for (int i = 0; i < blockSize; ++i) {               // fix the row
                    for (int j = 0; j < blockSize; ++j) {           // fix the col
                        for (int k = 0; k < blockSize; ++k) {       // iterate inside fixed row/col
                            C[bi + i][bj + j] += (A[bi + i][bk + k] * B[bk + k][bj + j]);
                        }
                    }
                }
            }
        }
    }
    // A single k is sufficient because A_column = B_row for matrix multiplication.

    print_matrix(C);

    return 0;
}
