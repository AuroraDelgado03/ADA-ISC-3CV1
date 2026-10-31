#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <psapi.h>
#else
    #include <sys/resource.h>
#endif

typedef struct Nodo {
    double valor;
    struct Nodo* izq;
    struct Nodo* der;
} Nodo;

Nodo* crearNodo(double valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error: Memoria RAM insuficiente.\n");
        exit(1);
    }
    nuevo->valor = valor;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

Nodo* insertar(Nodo* raiz, double valor) {
    if (raiz == NULL) return crearNodo(valor);
    if (valor < raiz->valor) {
        raiz->izq = insertar(raiz->izq, valor);
    } else {
        raiz->der = insertar(raiz->der, valor);
    }
    return raiz;
}

void inorden(Nodo* raiz, double arreglo[], long* indice) {
    if (raiz != NULL) {
        inorden(raiz->izq, arreglo, indice);
        arreglo[*indice] = raiz->valor;
        (*indice)++;
        inorden(raiz->der, arreglo, indice);
    }
}

void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izq);
        liberarArbol(raiz->der);
        free(raiz);
    }
}


double obtenerMemoriaMB() {
#if defined(_WIN32) || defined(_WIN64)
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return (double)pmc.WorkingSetSize / (1024.0 * 1024.0); 
#else
    struct rusage uso;
    getrusage(RUSAGE_SELF, &uso);
    return (double)uso.ru_maxrss / 1024.0; 
#endif
}

void evaluarTamano(long n) {
    printf("\nGenerando %ld numeros reales (double)...\n", n);
    
    double* datos = (double*)malloc(sizeof(double) * n);
    if (!datos) {
        printf("Error: No se pudo asignar memoria para el arreglo base.\n");
        return;
    }

    for (long i = 0; i < n; i++) {
        datos[i] = ((double)rand() / RAND_MAX) * 1000.0;
    }

   
    clock_t inicio = clock();

   
    Nodo* raiz = NULL;
    for (long i = 0; i < n; i++) {
        raiz = insertar(raiz, datos[i]);
    }

    
    long indice = 0;
    inorden(raiz, datos, &indice);

   
    clock_t fin = clock();
    double tiempo_seg = (double)(fin - inicio) / CLOCKS_PER_SEC;

    
    double memoria_mb = obtenerMemoriaMB();

    printf("-> Completo para n = %ld\n", n);
    printf("   Tiempo: %.4f segundos\n", tiempo_seg);
    printf("   Memoria pico: %.2f MB\n", memoria_mb);

    
    liberarArbol(raiz);
    free(datos);
}

int main() {
    srand((unsigned int)time(NULL));

    long tamanos[] = {100000, 1000000, 10000000,100000000,1000000000};
    int num_pruebas = sizeof(tamanos) / sizeof(tamanos[0]);

    printf("INICIANDO BENCHMARK TREE SORT\n");
    for (int i = 0; i < num_pruebas; i++) {
        evaluarTamano(tamanos[i]);
    }

    return 0;
}