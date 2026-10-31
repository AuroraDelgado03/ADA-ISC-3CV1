import random
import time
import sys

# Aumentar el límite de enteros a strings por si imprime valores muy grandes
sys.set_int_max_str_digits(10000000)

print("Ingresa la cantidad de numeros: ")
n = int(input())

number = []
for i in range(n):
    aleatorio = random.randint(1, n)
    number.append(aleatorio)

# INICIA MEDICIÓN DEL ORDENAMIENTO COUNTING SORT

inicio_ordenamiento = time.time()

# Generación de la lista auxiliar para evitar ciclos lentos en Python
count = [0] * (n + 1)

# Paso 1: Contar las frecuencias
for i in range(n):
    valor_actual = number[i]
    count[valor_actual] = count[valor_actual] + 1

# Paso 2: Reconstruir la lista original en orden
indice = 0
for i in range(1, n + 1):
    while count[i] > 0:
        number[indice] = i
        indice = indice + 1
        count[i] = count[i] - 1

fin_ordenamiento = time.time()
tiempo_ordenamiento = fin_ordenamiento - inicio_ordenamiento
# =======================================================

max_val = number[n - 1]
min_val = number[0]
print("\nEl numero maximo es:", max_val)
print("El numero minimo es:", min_val)

print("\nQue numero deseas buscar: ")
search = int(input())

low = 0
high = n - 1
found = 0

# INICIA MEDICIÓN DE LA BÚSQUEDA BINARIA
inicio_busqueda = time.time()

while low <= high:
    mid = low + (high - low) // 2
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

print("\n--- TIEMPOS---")
print("Tiempo Ordenamiento (Counting Sort):", tiempo_ordenamiento, "segundos")
print("Tiempo Busqueda Binaria:", tiempo_busqueda, "segundos")
