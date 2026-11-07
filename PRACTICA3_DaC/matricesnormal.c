#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + 
           (end.tv_nsec - start.tv_nsec) / 1000000.0;
}


void tradicional_1d(int n, int* A, int* B, int* C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}


int** crear_matriz_2d(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
    }
    return mat;
}

void liberar_matriz_2d(int** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

void tradicional_2d(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void imprimir_consumo_memoria(int n) {
    // Memoria para una sola matriz en int* (1D) vs int** (2D)
    size_t bytes_1d = (size_t)n * n * sizeof(int);
    
    // En 2D: n punteros (int*) + n*n enteros (int)
    size_t bytes_2d = ((size_t)n * sizeof(int*)) + ((size_t)n * n * sizeof(int));

    printf("  [Memoria por matriz] 1D Contiguo: %.2f KB | 2D Dinámico: %.2f KB\n", 
            bytes_1d / 1024.0, bytes_2d / 1024.0);
}

int main() {
    int tamanos[] = {16, 32, 64, 128, 256, 512};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    struct timespec start, end;

    printf("=== MULTIPLICACIÓN TRADICIONAL ===\n\n");

    for (int idx = 0; idx < num_tamanos; idx++) {
        int n = tamanos[idx];
        printf("--- Tamaño n = %d ---\n", n);
        imprimir_consumo_memoria(n);

        // Benchmark 1D
        int *A1D = (int*)malloc(n * n * sizeof(int));
        int *B1D = (int*)malloc(n * n * sizeof(int));
        int *C1D = (int*)malloc(n * n * sizeof(int));

        for (int i = 0; i < n * n; i++) {
            A1D[i] = rand() % 10;
            B1D[i] = rand() % 10;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        tradicional_1d(n, A1D, B1D, C1D);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("  1D Contiguo: %.3f ms\n", get_time_ms(start, end));

        free(A1D); free(B1D); free(C1D);

        // Benchmark 2D
        int** A2D = crear_matriz_2d(n);
        int** B2D = crear_matriz_2d(n);
        int** C2D = crear_matriz_2d(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A2D[i][j] = rand() % 10;
                B2D[i][j] = rand() % 10;
            }
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        tradicional_2d(n, A2D, B2D, C2D);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("  2D Dinámico: %.3f ms\n\n", get_time_ms(start, end));

        liberar_matriz_2d(A2D, n);
        liberar_matriz_2d(B2D, n);
        liberar_matriz_2d(C2D, n);
    }

    return 0;
}