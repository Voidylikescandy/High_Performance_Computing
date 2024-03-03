#include <stdio.h>

#define N 10

int main(int argc, char* argv[]) {
    int A[N][N];
    int x[N];
    int y[N];

    for (int i = 0; i < N; ++i) {
        x[i] = 1;
        y[i] = 0;
        for (int j = 0; j < N; ++j)
            A[i][j] = 1; 
    }

    printf("A = \n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("x = \n");
    for (int i = 0; i < N; ++i) {
        printf("%d\n", x[i]);
    }
    

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            y[i] = y[i] + A[i][j] * x[i];
        }
    }

    printf("y = \n");
    for (int i = 0; i < N; ++i) {
        printf("%d\n", y[i]);
    }
}