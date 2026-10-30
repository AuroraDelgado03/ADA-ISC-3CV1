#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Búsqueda secuencial optimizada
long long busqueda_secuencial(const int *arr, long long n, int objetivo) {
    long long i;
    for (i = 0; i < n; i++) {
        if (arr[i] == objetivo) {
            return i; 
        }
    }
    return -1; // Retorna -1 si no lo encuentra (peor caso)
}

int main() {
    long long tamanios[] = {1000, 10000, 100000, 1000000, 10000000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);

    srand(time(NULL));

    printf("--- BÚSQUEDA SECUENCIAL EN C (PEOR CASO: NO ENCONTRADO) ---\n");
    int t;
    for (t = 0; t < num_tamanios; t++) {
        long long n = tamanios[t];
        
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Error de asignación de memoria\n");
            return 1;
        }

        // Generar dataset con números positivos aleatorios
        long long i;
        for (i = 0; i < n; i++) {
            arr[i] = rand() % 1000000 + 1;
        }

        // PEOR CASO: Buscamos -1, un valor garantizado de no existir en el arreglo
        int objetivo = -1;

        clock_t inicio = clock();
        long long resultado = busqueda_secuencial(arr, n, objetivo);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tamaño: %-10lld | Tiempo: %.6f segundos | Resultado: %lld (No encontrado)\n", n, tiempo, resultado);

        free(arr);
    }

    return 0;
}
