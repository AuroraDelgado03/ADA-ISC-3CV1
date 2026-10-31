import random
import time

# Entrada del usuario por consola
print("Ingresa la cantidad de numeros: ")
n = int(input())

# Crear un arreglo (lista) dinámico vacío
number = []

# Llenar el arreglo con números aleatorios del 1 al n
for i in range(n):
    aleatorio = random.randint(1, n)
    number.append(aleatorio)

# =======================================================
# INICIA MEDICIÓN DEL ORDENAMIENTO BUBBLE SORT
# =======================================================
inicio_ordenamiento = time.time()

# Ordenamiento Bubble Sort tradicional con dos ciclos anidados
for i in range(0, n - 1):
    for j in range(0, n - i - 1):
        if number[j] > number[j + 1]:
            temp = number[j]
            number[j] = number[j + 1]
            number[j + 1] = temp

fin_ordenamiento = time.time()
tiempo_ordenamiento = fin_ordenamiento - inicio_ordenamiento
# =======================================================

# Encontrar los extremos de la lista ordenada
max_val = number[n - 1]
min_val = number[0]

print("\nEl numero maximo es:", max_val)
print("El numero minimo es:", min_val)

print("\nQue numero deseas buscar: ")
search = int(input())

# Variables de la búsqueda binaria
low = 0
high = n - 1
found = 0

# =======================================================
# INICIA MEDICIÓN DE LA BÚSQUEDA BINARIA
# =======================================================
inicio_busqueda = time.time()

# Ciclo de búsqueda binaria tradicional
while low <= high:
    mid = low + (high - low) // 2  # '//' asegura división entera en Python

    if number[mid] == search:
        print("El numero", search, "se encuentra en el indice", mid)
        found = 1
        break
    
    if search < number[mid]:
        high = mid - 1
    else:
        low = mid + 1

fin_busqueda = time.time()
tiempo_busqueda = fin_busqueda - inicio_busqueda
# =======================================================

if found == 0:
    print("El numero", search, "no se encuentra en el array.")

# Impresión de tiempos

print("Tiempo Ordenamiento (Burbuja):", tiempo_ordenamiento, "segundos")
print("Tiempo Busqueda Binaria:", tiempo_busqueda, "segundos")
