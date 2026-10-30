// Importar librerías
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funcion para acomodar los elementos del Max-Heap
void heapify(double arreglo[], int n, int i) {
    int mayor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    // Compara el hijo izquierdo con la raiz
    if (izquierda < n && arreglo[izquierda] > arreglo[mayor]) {
        mayor = izquierda;
    }

    // Compara el hijo derecho con el mayor actual
    if (derecha < n && arreglo[derecha] > arreglo[mayor]) {
        mayor = derecha;
    }

    // Si el mayor no es la raiz, intercambia
    if (mayor != i) {
        double temporal = arreglo[i];
        arreglo[i] = arreglo[mayor];
        arreglo[mayor] = temporal;
        // Continua acomodando el monticulo
        heapify(arreglo, n, mayor);
    }
}


// Funcion principal de Heapsort
void heapsort(double arreglo[], int n) {
    int i;
    // Construye el Max-Heap
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arreglo, n, i);
    }

    // Extrae los elementos uno por uno
    for (i = n - 1; i > 0; i--) {
        // Coloca el mayor al final
        double temporal = arreglo[0];
        arreglo[0] = arreglo[i];
        arreglo[i] = temporal;

        // Reorganiza el monticulo
        heapify(arreglo, i, 0);
    }
}


int main() {
    int tamanos[] = {100000, 1000000, 10000000, 100000000, 1000000000};
    int cantidad = 5;

    srand(time(NULL));
    printf("Tamano\t\tTiempo (segundos)\tMemoria (MB)\n");
    int j;
    for (j = 0; j < cantidad; j++) {
        int n = tamanos[j];
        printf("\nGenerando arreglo de %d elementos...\n", n);
        // Reserva memoria para el arreglo
        double *arreglo = malloc((size_t)n * sizeof(double));
        if (arreglo == NULL) {
            printf("No hay memoria suficiente.\n");
            break;
        }
        int i;
        // Genera numeros reales aleatorios
        for (i = 0; i < n; i++) {
            arreglo[i] = ((double)rand() / RAND_MAX) * 1000000.0;
        }

        // Calcula la memoria utilizada
        double memoria = ((double)n * sizeof(double)) / (1024.0 * 1024.0);
        // Mide el tiempo de ejecucion
        clock_t inicio = clock();
        heapsort(arreglo, n);
        clock_t fin = clock();
        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("%d\t\t%.6f\t\t%.2f\n", n, tiempo, memoria);
        // Libera la memoria
        free(arreglo);
    }
    return 0;
}
