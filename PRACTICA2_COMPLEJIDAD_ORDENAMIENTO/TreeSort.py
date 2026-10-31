import sys
import time
import tracemalloc
import random


sys.setrecursionlimit(2_000_000)

class Nodo:
    __slots__ = ('valor', 'izq', 'der')
    def __init__(self, valor):
        self.valor = valor
        self.izq = None
        self.der = None

def insertar(raiz, valor):
    if raiz is None:
        return Nodo(valor)
    if valor < raiz.valor:
        raiz.izq = insertar(raiz.izq, valor)
    else:
        raiz.der = insertar(raiz.der, valor)
    return raiz

def inorden(raiz, lista_ordenada):
    if raiz is not None:
        inorden(raiz.izq, lista_ordenada)
        lista_ordenada.append(raiz.valor)
        inorden(raiz.der, lista_ordenada)


def evaluar_tamano(n):
    print(f"\nGenerando {n:,} números reales aleatorios...")
    datos = [random.uniform(0.0, 1000.0) for _ in range(n)]
    
    
    tracemalloc.start()
    tiempo_inicio = time.perf_counter()
    

    raiz = None
    for item in datos:
        raiz = insertar(raiz, item)
        
    arreglo_ordenado = []
    inorden(raiz, arreglo_ordenado)
    

    tiempo_fin = time.perf_counter()
    _, memoria_pico = tracemalloc.get_traced_memory()
    tracemalloc.stop()

    
    tiempo_seg = tiempo_fin - tiempo_inicio
    memoria_mb = memoria_pico / (1024 * 1024)
    print(f"-> Completo para n = {n:,}")
    print(f"   Tiempo: {tiempo_seg:.4f} segundos")
    print(f"   Memoria pico: {memoria_mb:.2f} MB")


if __name__ == "__main__":

    tamanos = [100_000, 1_000_000, 10_000_000, 100_000_000, 1_000_000_000]
    
    print("=== INICIANDO BENCHMARK TREE SORT (PYTHON) ===")
    for n in tamanos:
        evaluar_tamano(n)