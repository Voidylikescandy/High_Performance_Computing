#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 8
int blockSize = N / 2;
int A[N][N];
int B[N][N];
int C[N][N];
pthread_mutex_t mutex;

typedef struct block_parameters {
    int bi;
    int bj;
    int bk;
} block_parameters;

void* multiply_block(void *args) {
    block_parameters* parameters = (block_parameters*) args;

    int bi = parameters->bi;
    int bj = parameters->bj;
    int bk = parameters->bk;

    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            for (int k = 0; k < blockSize; ++k) {
                int a = A[bi + i][bk + k];
                int b = B[bk + k][bj + j];
                int c = a * b;
                pthread_mutex_lock(&mutex);
                C[bi + i][bj + j] += c;
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    free(parameters);
    return NULL;
}

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
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 3;
            B[i][j] = 2;
            C[i][j] = 0;
        }
    }

    print_matrix(A);
    print_matrix(B);

    pthread_t threads[8];
    int thread_count = 0;

    for (int bi = 0; bi < N; bi += blockSize) {
        for (int bj = 0; bj < N; bj += blockSize) {
            for (int bk = 0; bk < N; bk += blockSize) {
                
                block_parameters* parameters = (block_parameters*)malloc(sizeof(block_parameters));
                parameters->bi = bi;
                parameters->bj = bj;
                parameters->bk = bk;

                pthread_create(&threads[thread_count++], NULL, multiply_block, parameters);
            }
        }
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    print_matrix(C);

    pthread_mutex_destroy(&mutex);

    return 0;
}
