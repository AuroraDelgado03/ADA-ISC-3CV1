# Importar librerías
import random
import time
import sys
from array import array

# Funcion para acomodar los elementos del Max-Heap
def heapify(arreglo, n, i):
    while True:
        mayor = i
        izquierda = 2 * i + 1
        derecha = 2 * i + 2

        # Compara el hijo izquierdo con la raiz
        if izquierda < n and arreglo[izquierda] > arreglo[mayor]:
            mayor = izquierda
        # Compara el hijo derecho con el mayor actual
        if derecha < n and arreglo[derecha] > arreglo[mayor]:
            mayor = derecha
        # Si el mayor no es la raiz, intercambia
        if mayor == i:
            break
        arreglo[i], arreglo[mayor] = arreglo[mayor], arreglo[i]
        i = mayor


# Funcion principal de Heapsort
def heapsort(arreglo):
    n = len(arreglo)
    # Construye el Max-Heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arreglo, n, i)
    # Extrae los elementos uno por uno
    for i in range(n - 1, 0, -1):
        # Coloca el mayor al final
        arreglo[0], arreglo[i] = arreglo[i], arreglo[0]
        # Reorganiza el monticulo
        heapify(arreglo, i, 0)


# Tamaños de los arreglos solicitados
tamanos = [100000, 1000000, 10000000, 100000000, 1000000000]

print("Tamano\t\tTiempo (segundos)\tMemoria (MB)")

for n in tamanos:
    print(f"\nGenerando arreglo de {n} elementos...")
    # Genera numeros reales aleatorios
    arreglo = array('d',
        (random.uniform(0, 1000000) for i in range(n))
    )

    # Calcula la memoria utilizada por el arreglo
    memoria = sys.getsizeof(arreglo) / (1024 * 1024)
    # Mide el tiempo de ejecucion
    inicio = time.perf_counter()
    heapsort(arreglo)
    fin = time.perf_counter()
    tiempo = fin - inicio
    print(f"{n}\t\t{tiempo:.6f}\t\t{memoria:.2f}")
    del arreglo
