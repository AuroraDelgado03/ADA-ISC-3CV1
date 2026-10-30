# Medir tiempo en Python
# Genera arreglos aleatorios de los tamaños solicitados, busca un 
# elemento inexistente, mide el tiempo y calcula promedios.

import random
import time

# Parámetros: El arreglo a recorrer y el número que se busca
def busqueda_secuencial(arreglo, objetivo):
    for num in range(len(arreglo)): # Genera índices [0-último índice]
        if arreglo[num] == objetivo:
            return num # Devuelve la posición de objetivo
    return -1 # Indica que objetivo no existe dentro de arreglo

tamanos = [1000, 10000, 100000, 1000000, 10000000]

print("Tamano\t\tTiempo (segundos)")

for n in tamanos:
    # Genera los datos aleatorios.
    arreglo = [random.randint(0, 1000000000)
        for i in range(n)]

    objetivo = -1 # Valor a buscar

    inicio = time.perf_counter()
    resultado = busqueda_secuencial(arreglo, objetivo)
    fin = time.perf_counter()

    tiempo = fin - inicio 

    print(f"{n}\t\t{tiempo:.6f}")
