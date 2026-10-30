// Medir tiempo en C
// Genera arreglos aleatorios de los tamaños solicitados, busca un 
// elemento inexistente, mide el tiempo y calcula promedios.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Parámetros: arreglo a recorrer, núm. de elementos y el núm. a buscar 
int busqueda_secuencial(int arreglo[], int n, int objetivo) {
    int i;
    for (i = 0; i < n; i++) {
        if (arreglo[i] == objetivo) {
            return i; // Devuelve la posición de objetivo
        }
    }
    return -1; // Indica que objetivo no existe dentro de arreglo
}

int main(void) {
    int tamanos[] = {
        1000, 10000, 100000, 1000000, 10000000
    };

    // Declara un arreglo que guarda los tamaños de las pruebas
    int cantidad = sizeof(tamanos) / sizeof(tamanos[0]);

    // Inicializar el generador de núm. aleatorios
    srand((unsigned int)time(NULL));

    printf("Tamano\t\tTiempo (segundos)\n");

    // Recorre la lista de tamanos
    int j;
    for (j = 0; j < cantidad; j++) {
        int n = tamanos[j];

        // Reservar memoria
        int *arreglo = malloc((size_t)n * sizeof(int));

        if (arreglo == NULL) {
            printf("No se pudo reservar memoria para %d elementos\n", n);
            return 1;
        }

        // Generar los datos aleatorios
        int i;
        for (i = 0; i < n; i++) {
            arreglo[i] = rand();
        }

        clock_t inicio = clock();

        int resultado = busqueda_secuencial(arreglo, n, -1);

        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("%d\t\t%.6f\n", n, tiempo);

        free(arreglo);
        (void)resultado;
    }
    return 0;
}
