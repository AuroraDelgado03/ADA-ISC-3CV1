#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n, i, j;
    srand(time(NULL)); // Inicializa la generación de números aleatorios
    
    printf("Ingresa la cantidad de numeros: ");
    scanf("%d", &n);
    
    int *number = (int *)malloc(n * sizeof(int)); // Reservando memoria para el dataset principal
    if (number == NULL) {
        printf("Error: No hay suficiente memoria ram para este dataset.\n");
        return 1;
    }
    
    for (i=0; i<n; i++){
        number[i] = rand() % n + 1; // Asignando valores aleatorios enteros del 1 al n
    }

    // =======================================================
    // INICIA MEDICIÓN DEL ORDENAMIENTO COUNTING SORT
    // =======================================================
    clock_t inicio_ordenamiento = clock();
    
    // Usamos malloc para el conteo, indispensable para soportar datasets gigantes sin crashear
    int *count = (int *)malloc((n + 1) * sizeof(int));
    if (count == NULL) {
        printf("Error: Memoria insuficiente para el arreglo de conteo.\n");
        free(number);
        return 1;
    }

    // Inicializar el arreglo de conteo en ceros
    for (i = 0; i <= n; i++) {
        count[i] = 0;
    }

    // Paso 1: Contar cuántas veces sale cada número
    for (i = 0; i < n; i++) {
        count[number[i]] = count[number[i]] + 1;
    }

    // Paso 2: Volver a meter los números ordenados al arreglo original
    int indice = 0;
    for (i = 1; i <= n; i++) {
        for (j = 0; j < count[i]; j++) {
            number[indice] = i;
            indice = indice + 1;
        }
    }
    
    clock_t fin_ordenamiento = clock();
    double tiempo_ordenamiento = (double)(fin_ordenamiento - inicio_ordenamiento) / CLOCKS_PER_SEC;
    // =======================================================
    
    int max = number[n-1];
    int min = number[0];
    
    
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
            break; 
        }
        
        (search < number[mid]) ? (high = mid - 1) : (low = mid + 1);
    }
    
    clock_t fin_busqueda = clock();
    double tiempo_busqueda = (double)(fin_busqueda - inicio_busqueda) / CLOCKS_PER_SEC;
    // =======================================================
    
    if (!found) {
        printf("El numero %d no se encuentra en el array.\n", search);
    }

    printf("\n--- TIEMPOS---\n");
    printf("Tiempo Ordenamiento (Counting Sort): %f segundos\n", tiempo_ordenamiento);
    printf("Tiempo Busqueda Binaria: %f segundos\n", tiempo_busqueda);
    
    free(count);   // Liberando memoria auxiliar
    free(number);  // Liberando memoria dinámica principal
    return 0; 
}
