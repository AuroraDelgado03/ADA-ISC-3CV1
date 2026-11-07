import time
import tracemalloc
import random
def traditional_mult_2d(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for k in range(n):
            for j in range(n):
                C[i][j] += A[i][k] * B[k][j]
    return C
def traditional_mult_1d(A, B, n):
    C = [0] * (n * n)
    for i in range(n):
        for k in range(n):
            for j in range(n):
                # Cálculo de índices: i*n + j
                C[i * n + j] += A[i * n + k] * B[k * n + j]
    return C
def add_2d(A, B):
    n = len(A)
    return [[A[i][j] + B[i][j] for j in range(n)] for i in range(n)]
def sub_2d(A, B):
    n = len(A)
    return [[A[i][j] - B[i][j] for j in range(n)] for i in range(n)]
def split_2d(A):
    n = len(A)
    mid = n // 2
    A11 = [row[:mid] for row in A[:mid]]
    A12 = [row[mid:] for row in A[:mid]]
    A21 = [row[:mid] for row in A[mid:]]
    A22 = [row[mid:] for row in A[mid:]]
    return A11, A12, A21, A22
def strassen_2d(A, B, leaf_size=16):
    n = len(A)
    if n <= leaf_size:
        return traditional_mult_2d(A, B)  
    A11, A12, A21, A22 = split_2d(A)
    B11, B12, B21, B22 = split_2d(B)
    P1 = strassen_2d(add_2d(A11, A22), add_2d(B11, B22), leaf_size)
    P2 = strassen_2d(add_2d(A21, A22), B11, leaf_size)
    P3 = strassen_2d(A11, sub_2d(B12, B22), leaf_size)
    P4 = strassen_2d(A22, sub_2d(B21, B11), leaf_size)
    P5 = strassen_2d(add_2d(A11, A12), B22, leaf_size)
    P6 = strassen_2d(sub_2d(A21, A11), add_2d(B11, B12), leaf_size)
    P7 = strassen_2d(sub_2d(A12, A22), add_2d(B21, B22), leaf_size)
    C11 = add_2d(sub_2d(add_2d(P1, P4), P5), P7)
    C12 = add_2d(P3, P5)
    C21 = add_2d(P2, P4)
    C22 = add_2d(sub_2d(add_2d(P1, P3), P2), P6)
    C = []
    for i in range(len(C11)):
        C.append(C11[i] + C12[i])
    for i in range(len(C21)):
        C.append(C21[i] + C22[i]) 
    return C
def add_1d(A, B, n):
    return [A[i] + B[i] for i in range(n * n)]
def sub_1d(A, B, n):
    return [A[i] - B[i] for i in range(n * n)]
def split_1d(A, n):
    mid = n // 2
    A11, A12, A21, A22 = [], [], [], []
    for i in range(mid):
        row_start = i * n
        A11.extend(A[row_start : row_start + mid])
        A12.extend(A[row_start + mid : row_start + n])
        row_start_lower = (i + mid) * n
        A21.extend(A[row_start_lower : row_start_lower + mid])
        A22.extend(A[row_start_lower + mid : row_start_lower + n])
        
    return A11, A12, A21, A22
def strassen_1d(A, B, n, leaf_size=16):
    if n <= leaf_size:
        return traditional_mult_1d(A, B, n)
    mid = n // 2
    A11, A12, A21, A22 = split_1d(A, n)
    B11, B12, B21, B22 = split_1d(B, n)
    P1 = strassen_1d(add_1d(A11, A22, mid), add_1d(B11, B22, mid), mid, leaf_size)
    P2 = strassen_1d(add_1d(A21, A22, mid), B11, mid, leaf_size)
    P3 = strassen_1d(A11, sub_1d(B12, B22, mid), mid, leaf_size)
    P4 = strassen_1d(A22, sub_1d(B21, B11, mid), mid, leaf_size)
    P5 = strassen_1d(add_1d(A11, A12, mid), B22, mid, leaf_size)
    P6 = strassen_1d(sub_1d(A21, A11, mid), add_1d(B11, B12, mid), mid, leaf_size)
    P7 = strassen_1d(sub_1d(A12, A22, mid), add_1d(B21, B22, mid), mid, leaf_size)
    C11 = add_1d(sub_1d(add_1d(P1, P4, mid), P5, mid), P7, mid)
    C12 = add_1d(P3, P5, mid)
    C21 = add_1d(P2, P4, mid)
    C22 = add_1d(sub_1d(add_1d(P1, P3, mid), P2, mid), P6, mid)
    C = [0] * (n * n)
    for i in range(mid):
        C[i * n : i * n + mid] = C11[i * mid : (i + 1) * mid]
        C[i * n + mid : (i + 1) * n] = C12[i * mid : (i + 1) * mid]
        lower_row = i + mid
        C[lower_row * n : lower_row * n + mid] = C21[i * mid : (i + 1) * mid]
        C[lower_row * n + mid : (lower_row + 1) * n] = C22[i * mid : (i + 1) * mid]
    return C
def run_benchmark():
    sizes = [16, 32, 64, 128, 256, 512]
    print(f"{'N':<5} | {'Algoritmo':<20} | {'Estructura':<10} | {'Tiempo (s)':<12} | {'Memoria Pico (MB)':<15}")
    print("-" * 75)
    for n in sizes:
        matA_2d = [[random.randint(1, 10) for _ in range(n)] for _ in range(n)]
        matB_2d = [[random.randint(1, 10) for _ in range(n)] for _ in range(n)]
        matA_1d = [item for sublist in matA_2d for item in sublist]
        matB_1d = [item for sublist in matB_2d for item in sublist]
        test_cases = [
            ("Tradicional", "2D", traditional_mult_2d, (matA_2d, matB_2d)),
            ("Tradicional", "1D", traditional_mult_1d, (matA_1d, matB_1d, n)),
            ("Strassen", "2D", strassen_2d, (matA_2d, matB_2d)),
            ("Strassen", "1D", strassen_1d, (matA_1d, matB_1d, n))
        ]
        for name, structure, func, args in test_cases:
            tracemalloc.start()
            start_time = time.perf_counter()
            _ = func(*args)
            end_time = time.perf_counter()
            current, peak = tracemalloc.get_traced_memory()
            tracemalloc.stop()
            elapsed_time = end_time - start_time
            peak_mb = peak / (1024 * 1024)
            print(f"{n:<5} | {name:<20} | {structure:<10} | {elapsed_time:<12.5f} | {peak_mb:<15.5f}")
        print("-" * 75)
if __name__ == "__main__":
    import sys
    sys.setrecursionlimit(5000)
    print("Iniciando Benchmarking. Esto tomará varios segundos/minutos dependiendo del hardware...")
    run_benchmark()