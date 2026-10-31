#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main(){
    int n, i, j, temp;
    srand(time(NULL)); // Inicializa la generación de números aleatorios
    
    
    printf("Ingresa la cantidad de numeros: ");
    scanf("%d", &n);
    int *number = (int *)malloc(n * sizeof(int)); // Reservando memoria para n enteros
    
    for (i=0; i<n; i++){
        number[i] = rand() % n + 1; // Asignando valores aleatorios del 1 al n
    }

    // =======================================================
    // INICIA MEDICIÓN DEL ORDENAMIENTO BUBBLE SORT
    // =======================================================
    clock_t inicio_ordenamiento = clock();

    // Ordenamiento Bubble Sort
    for (i=0; i<n-1; i++){
        for (j=0; j<n-i-1; j++){
            if (number[j] > number[j+1]){
                temp = number[j];
                number[j] = number[j+1];
                number[j+1] = temp;
            }
        }
    }
    
    clock_t fin_ordenamiento = clock();
    double tiempo_ordenamiento = (double)(fin_ordenamiento - inicio_ordenamiento) / CLOCKS_PER_SEC;
    // =======================================================
    
    int max = number[n-1];
    int min = number[0];
    
    printf("\nlista ordenada: ");
    for (i=0; i<n; i++){
        printf("%d ", number[i]);
    }

    printf("\nEl numero maximo es: %d \n", max);
    printf("El numero minimo es: %d \n", min);
    
    printf("\nQue numero deseas buscar: ");
    int search;
    scanf("%d", &search);

    // VARIABLES DE BÚSQUEDA BINARIA
    int low = 0;
    int high = n - 1;
    int mid; 
    int found = 0;

    // =======================================================
    // INICIA MEDICIÓN DE LA BÚSQUEDA BINARIA
    // =======================================================
    clock_t inicio_busqueda = clock();

    // Ciclo de búsqueda binaria usando el operador ternario
    for (i = 0; low <= high; i++){
        mid = low + (high - low) / 2;

        if (number[mid] == search) {
            printf("El numero %d se encuentra en el indice %d\n", search, mid);
            found = 1;
            break; // Detiene el ciclo porque ya encontramos el valor
        }
        
        
        // Si el valor buscado es menor al del medio, reduce 'high'. Si es mayor, aumenta 'low'.
        (search < number[mid]) ? (high = mid - 1) : (low = mid + 1);
    }
    
    clock_t fin_busqueda = clock();
    double tiempo_busqueda = (double)(fin_busqueda - inicio_busqueda) / CLOCKS_PER_SEC;
    // =======================================================
    
    if (!found) {
        printf("El numero %d no se encuentra en el array.\n", search);
    }

    // IMPRESIÓN EXTRAS DE TIEMPOS AL FINAL DEL PROGRAMA
    printf("\n--- TIEMPOS PARA TU REPORTE ---\n");
    printf("Tiempo Ordenamiento (Burbuja): %f segundos\n", tiempo_ordenamiento);
    printf("Tiempo Busqueda Binaria: %f segundos\n", tiempo_busqueda);

    free(number); // Liberando la memoria dinámica

    return 0; 
}

