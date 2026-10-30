# Búsqueda secuencial en Python

# Implementa la búsqueda secuencial en Python con un arreglo pequeño.
# Sirve para comprobar el funcionamiento del algoritmo y verificar los 
# casos en los que el elemento existe o no existe.

def busqueda_secuencial(arreglo, objetivo):
    for i in range(len(arreglo)):
        if arreglo[i] == objetivo:
            return i

    return -1


numeros = [12, 7, 25, 4, 18]
objetivo = 50

resultado = busqueda_secuencial(numeros, objetivo)

if resultado != -1:
    print(f"Elemento encontrado en el indice {resultado}")
else:
    print("Elemento no encontrado")
