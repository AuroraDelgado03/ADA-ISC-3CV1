// Búsqueda secuencial en C

// Implementa la búsqueda secuencial en C con un arreglo pequeño.
// Sirve para comprobar la lógica del algoritmo y verificar los 
// casos en los que el elemento existe o no existe.

#include <stdio.h>

int busqueda_secuencial(int arreglo[], int n, int objetivo) {
    int i;
    for (i = 0; i < n; i++) {
        if (arreglo[i] == objetivo) {
            return i;
        }
    }

    return -1;
}

int main(void) {
    int numeros[] = {12, 7, 25, 4, 18};
    int n = sizeof(numeros) / sizeof(numeros[0]);
    int objetivo = 50;

    int resultado = busqueda_secuencial(numeros, n, objetivo);

    if (resultado != -1) {
        printf("Elemento encontrado en el indice %d\n", resultado);
    } else {
        printf("Elemento no encontrado\n");
    }

    return 0;
}
