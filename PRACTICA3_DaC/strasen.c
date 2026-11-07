#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + 
           (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

void imprimir_consumo_memoria(int n) {
    // Memoria para una sola matriz en int* (1D) vs int** (2D)
    size_t bytes_1d = (size_t)n * n * sizeof(int);
    
    // En 2D: n punteros (int*) + n*n enteros (int)
    size_t bytes_2d = ((size_t)n * sizeof(int*)) + ((size_t)n * n * sizeof(int));

    printf("  [Memoria por matriz] 1D Contiguo: %.2f KB | 2D Dinámico: %.2f KB\n", 
            bytes_1d / 1024.0, bytes_2d / 1024.0);
}


void sumar_1d(int n, int* A, int* B, int* C) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] + B[i];
}

void restar_1d(int n, int* A, int* B, int* C) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] - B[i];
}

void strassen_1d(int n, int* A, int* B, int* C) {
    if (n <= 1) {
        C[0] = A[0] * B[0];
        return;
    }

    int k = n / 2;
    int size = k * k;

    int *A11 = (int*)malloc(size * sizeof(int));
    int *A12 = (int*)malloc(size * sizeof(int));
    int *A21 = (int*)malloc(size * sizeof(int));
    int *A22 = (int*)malloc(size * sizeof(int));

    int *B11 = (int*)malloc(size * sizeof(int));
    int *B12 = (int*)malloc(size * sizeof(int));
    int *B21 = (int*)malloc(size * sizeof(int));
    int *B22 = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i * k + j] = A[i * n + j];
            A12[i * k + j] = A[i * n + (j + k)];
            A21[i * k + j] = A[(i + k) * n + j];
            A22[i * k + j] = A[(i + k) * n + (j + k)];

            B11[i * k + j] = B[i * n + j];
            B12[i * k + j] = B[i * n + (j + k)];
            B21[i * k + j] = B[(i + k) * n + j];
            B22[i * k + j] = B[(i + k) * n + (j + k)];
        }
    }

    int *M1 = (int*)malloc(size * sizeof(int));
    int *M2 = (int*)malloc(size * sizeof(int));
    int *M3 = (int*)malloc(size * sizeof(int));
    int *M4 = (int*)malloc(size * sizeof(int));
    int *M5 = (int*)malloc(size * sizeof(int));
    int *M6 = (int*)malloc(size * sizeof(int));
    int *M7 = (int*)malloc(size * sizeof(int));

    int *tA = (int*)malloc(size * sizeof(int));
    int *tB = (int*)malloc(size * sizeof(int));

    sumar_1d(k, A11, A22, tA); sumar_1d(k, B11, B22, tB); strassen_1d(k, tA, tB, M1);
    sumar_1d(k, A21, A22, tA); strassen_1d(k, tA, B11, M2);
    restar_1d(k, B12, B22, tB); strassen_1d(k, A11, tB, M3);
    restar_1d(k, B21, B11, tB); strassen_1d(k, A22, tB, M4);
    sumar_1d(k, A11, A12, tA); strassen_1d(k, tA, B22, M5);
    restar_1d(k, A21, A11, tA); sumar_1d(k, B11, B12, tB); strassen_1d(k, tA, tB, M6);
    restar_1d(k, A12, A22, tA); sumar_1d(k, B21, B22, tB); strassen_1d(k, tA, tB, M7);

    int *C11 = (int*)malloc(size * sizeof(int));
    int *C12 = (int*)malloc(size * sizeof(int));
    int *C21 = (int*)malloc(size * sizeof(int));
    int *C22 = (int*)malloc(size * sizeof(int));

    sumar_1d(k, M1, M4, tA); restar_1d(k, tA, M5, tB); sumar_1d(k, tB, M7, C11);
    sumar_1d(k, M3, M5, C12);
    sumar_1d(k, M2, M4, C21);
    restar_1d(k, M1, M2, tA); sumar_1d(k, tA, M3, tB); sumar_1d(k, tB, M6, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i * n + j] = C11[i * k + j];
            C[i * n + (j + k)] = C12[i * k + j];
            C[(i + k) * n + j] = C21[i * k + j];
            C[(i + k) * n + (j + k)] = C22[i * k + j];
        }
    }

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(M1); free(M2); free(M3); free(M4); free(M5); free(M6); free(M7);
    free(tA); free(tB); free(C11); free(C12); free(C21); free(C22);
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

void sumar_2d(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void restar_2d(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen_2d(int n, int** A, int** B, int** C) {
    if (n <= 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int** A11 = crear_matriz_2d(k); int** A12 = crear_matriz_2d(k);
    int** A21 = crear_matriz_2d(k); int** A22 = crear_matriz_2d(k);
    int** B11 = crear_matriz_2d(k); int** B12 = crear_matriz_2d(k);
    int** B21 = crear_matriz_2d(k); int** B22 = crear_matriz_2d(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j]; A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j]; A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j]; B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j]; B22[i][j] = B[i + k][j + k];
        }
    }

    int** M1 = crear_matriz_2d(k); int** M2 = crear_matriz_2d(k);
    int** M3 = crear_matriz_2d(k); int** M4 = crear_matriz_2d(k);
    int** M5 = crear_matriz_2d(k); int** M6 = crear_matriz_2d(k);
    int** M7 = crear_matriz_2d(k);
    int** tA = crear_matriz_2d(k); int** tB = crear_matriz_2d(k);

    sumar_2d(k, A11, A22, tA); sumar_2d(k, B11, B22, tB); strassen_2d(k, tA, tB, M1);
    sumar_2d(k, A21, A22, tA); strassen_2d(k, tA, B11, M2);
    restar_2d(k, B12, B22, tB); strassen_2d(k, A11, tB, M3);
    restar_2d(k, B21, B11, tB); strassen_2d(k, A22, tB, M4);
    sumar_2d(k, A11, A12, tA); strassen_2d(k, tA, B22, M5);
    restar_2d(k, A21, A11, tA); sumar_2d(k, B11, B12, tB); strassen_2d(k, tA, tB, M6);
    restar_2d(k, A12, A22, tA); sumar_2d(k, B21, B22, tB); strassen_2d(k, tA, tB, M7);

    int** C11 = crear_matriz_2d(k); int** C12 = crear_matriz_2d(k);
    int** C21 = crear_matriz_2d(k); int** C22 = crear_matriz_2d(k);

    sumar_2d(k, M1, M4, tA); restar_2d(k, tA, M5, tB); sumar_2d(k, tB, M7, C11);
    sumar_2d(k, M3, M5, C12);
    sumar_2d(k, M2, M4, C21);
    restar_2d(k, M1, M2, tA); sumar_2d(k, tA, M3, tB); sumar_2d(k, tB, M6, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    liberar_matriz_2d(A11, k); liberar_matriz_2d(A12, k); liberar_matriz_2d(A21, k); liberar_matriz_2d(A22, k);
    liberar_matriz_2d(B11, k); liberar_matriz_2d(B12, k); liberar_matriz_2d(B21, k); liberar_matriz_2d(B22, k);
    liberar_matriz_2d(M1, k); liberar_matriz_2d(M2, k); liberar_matriz_2d(M3, k); liberar_matriz_2d(M4, k);
    liberar_matriz_2d(M5, k); liberar_matriz_2d(M6, k); liberar_matriz_2d(M7, k);
    liberar_matriz_2d(tA, k); liberar_matriz_2d(tB, k);
    liberar_matriz_2d(C11, k); liberar_matriz_2d(C12, k); liberar_matriz_2d(C21, k); liberar_matriz_2d(C22, k);
}


int main() {
    int tamanos[] = {16, 32, 64, 128, 256, 512};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    struct timespec start, end;

    printf("=== ALGORITMO DE STRASSEN ===\n\n");

    for (int idx = 0; idx < num_tamanos; idx++) {
        int n = tamanos[idx];
        printf("--- Tamano n = %d ---\n", n);
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
        strassen_1d(n, A1D, B1D, C1D);
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
        strassen_2d(n, A2D, B2D, C2D);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("  2D Dinamico: %.3f ms\n\n", get_time_ms(start, end));

        liberar_matriz_2d(A2D, n);
        liberar_matriz_2d(B2D, n);
        liberar_matriz_2d(C2D, n);
    }

    return 0;
}