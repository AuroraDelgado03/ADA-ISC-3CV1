import random
import time

def busqueda_secuencial(arr, objetivo):
    """Búsqueda secuencial recorriendo todo el arreglo."""
    for i in range(len(arr)):
        if arr[i] == objetivo:
            return i
    return -1  # Retorna -1 si no se encuentra (peor caso)

def main():
    tamanios = [1000, 10000, 100000, 1000000, 10000000]

    print(
        "--- BÚSQUEDA SECUENCIAL EN PYTHON (PEOR CASO: NO ENCONTRADO) ---"
    )
    for n in tamanios:
        # Generar dataset con números enteros positivos
        arr = [random.randint(1, n * 10) for _ in range(n)]

        # PEOR CASO: Buscamos -1, un valor que no está en el arreglo
        objetivo = -1

        inicio = time.perf_counter()
        resultado = busqueda_secuencial(arr, objetivo)
        fin = time.perf_counter()

        tiempo = fin - inicio
        print(
            f"Tamaño: {n:<10} | Tiempo: {tiempo:.6f} segundos | Resultado:"
            f" {resultado} (No encontrado)"
        )

if __name__ == "__main__":
    main()