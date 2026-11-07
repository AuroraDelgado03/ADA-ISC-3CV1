import random
import time


def particion(arr, low, high):
    p = random.randint(low, high)  # Pivote aleatorio para evitar el peor caso
    temp = arr[low]
    arr[low] = arr[p]
    arr[p] = temp

    pivot = arr[low]
    i = low + 1
    j = high

    while True:
        while i <= j and arr[i] <= pivot:
            i += 1
        while i <= j and arr[j] >= pivot:
            j -= 1

        if i > j:
            break

        temp = arr[i]
        arr[i] = arr[j]
        arr[j] = temp

    temp = arr[low]  # Ponemos el pivote en su posición final
    arr[low] = arr[j]
    arr[j] = temp

    return j


def quickselect(arr, k):
    low = 0
    high = len(arr) - 1

    while low < high:
        pos = particion(arr, low, high)

        if pos == k:
            return arr[pos]
        elif k < pos:
            high = pos - 1
        else:
            low = pos + 1

    return arr[low]


tamanos = [1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000]
max_valor = 10000000

print("--- TIEMPOS DEL QUICKSELECT ---")
print("n\tk\tDataset 1 (ms)\tDataset 2 (ms)")

for n in tamanos:
    k = random.randint(1, n)

    dataset_1 = []
    for i in range(n):
        dataset_1.append(random.randint(1, max_valor))

    inicio_1 = time.perf_counter()
    quickselect(dataset_1, k - 1)  # k - 1 porque el índice empieza en 0
    fin_1 = time.perf_counter()
    tiempo_1 = (fin_1 - inicio_1) * 1000

    dataset_2 = []
    for i in range(n):
        dataset_2.append(random.randint(1, max_valor))

    inicio_2 = time.perf_counter()
    quickselect(dataset_2, k - 1)
    fin_2 = time.perf_counter()
    tiempo_2 = (fin_2 - inicio_2) * 1000

    print(f"{n}\t{k}\t{tiempo_1:.4f}\t{tiempo_2:.4f}")
