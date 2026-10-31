import numpy as np
import time
import tracemalloc
import matplotlib.pyplot as plt
import pandas as pd
import gc
import psutil

def main():
    # Longitudes solicitadas
    sizes = [100_000, 1_000_000, 10_000_000, 100_000_000, 1_000_000_000]
    results = []

    for n in sizes:
        print(f"Evaluando N = {n:,}...")
        
        # Validación de memoria para evitar que la computadora se congele
        mem_available = psutil.virtual_memory().available
        required_memory = n * 8 * 2  # 8 bytes (float64) * 2 (arreglo original + auxiliar)
        
        if required_memory > mem_available:
            print(f"  -> OMITIDO: Requiere ~{required_memory / (1024**3):.2f} GB de RAM y solo hay {mem_available / (1024**3):.2f} GB disponibles.")
            results.append({
                'Tamaño (N)': n,
                'Tiempo (s)': None,
                'Memoria Pico (MB)': required_memory / (1024**2)
            })
            continue

        # Forzar recolección de basura antes de medir memoria
        gc.collect()
        tracemalloc.start()
        
        # Generar arreglo de números reales aleatorios (float64 por defecto en numpy)
        arr = np.random.rand(n)
        
        start_time = time.time()
        # Ordenamiento usando Mergesort
        arr_sorted = np.sort(arr, kind='mergesort')
        end_time = time.time()
        
        # Medición de memoria RAM pico
        current, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        
        exec_time = end_time - start_time
        # La memoria pico es al menos el tamaño teórico del arreglo duplicado
        peak_mb = max(peak / (1024 * 1024), (n * 8 * 2) / (1024 * 1024))
        
        results.append({
            'Tamaño (N)': n,
            'Tiempo (s)': exec_time,
            'Memoria Pico (MB)': peak_mb
        })
        
        # Liberar memoria explícitamente para la siguiente iteración
        del arr
        del arr_sorted
        gc.collect()

    # Guardar tabla de resultados en consola y CSV
    df = pd.DataFrame(results)
    df.to_csv("resultados_mergesort.csv", index=False)
    print("\n--- Resultados Finales ---")
    print(df.to_markdown())

    # Generación de la gráfica (excluyendo datos que dieron Out Of Memory)
    df_plot = df.dropna(subset=['Tiempo (s)']).copy()
    
    fig, ax1 = plt.subplots(figsize=(10, 6))

    color = 'tab:red'
    ax1.set_xlabel('Tamaño del Arreglo (N)')
    ax1.set_ylabel('Tiempo de Ejecución (s)', color=color)
    ax1.plot(df_plot['Tamaño (N)'], df_plot['Tiempo (s)'], marker='o', color=color, linewidth=2)
    ax1.tick_params(axis='y', labelcolor=color)
    ax1.set_xscale('log') # Escala logarítmica recomendada para variaciones grandes
    ax1.set_yscale('log')

    ax2 = ax1.twinx()
    color = 'tab:blue'
    ax2.set_ylabel('Memoria Consumida (MB)', color=color)
    ax2.plot(df_plot['Tamaño (N)'], df_plot['Memoria Pico (MB)'], marker='s', color=color, linewidth=2, linestyle='--')
    ax2.tick_params(axis='y', labelcolor=color)
    ax2.set_yscale('log')

    fig.tight_layout()
    plt.title('Evaluación de Complejidad: Algoritmo Mergesort')
    plt.grid(True, which="both", ls="--", alpha=0.3)
    plt.savefig('grafica_mergesort.png')
    print("\nGráfica guardada como 'grafica_mergesort.png'.")

if __name__ == '__main__':
    main()