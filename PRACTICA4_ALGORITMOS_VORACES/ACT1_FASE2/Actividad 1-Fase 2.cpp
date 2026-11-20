#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

struct Nodo {
    unsigned char c;
    long long frec;
    Nodo* izq;
    Nodo* der;
    Nodo(unsigned char c, long long frec, Nodo* izq = nullptr, Nodo* der = nullptr)
        : c(c), frec(frec), izq(izq), der(der) {}
};

struct Comparador {
    bool operator()(const Nodo* a, const Nodo* b) const {
        return a->frec > b->frec;
    }
};

void liberarArbol(Nodo* n) {
    if (!n) return;
    liberarArbol(n->izq);
    liberarArbol(n->der);
    delete n;
}

Nodo* construirArbol(const std::map<unsigned char, long long>& frecuencias) {
    std::priority_queue<Nodo*, std::vector<Nodo*>, Comparador> cola;
    for (const auto& par : frecuencias)
        cola.push(new Nodo(par.first, par.second));

    while (cola.size() > 1) {
        Nodo* a = cola.top(); cola.pop();
        Nodo* b = cola.top(); cola.pop();
        cola.push(new Nodo(0, a->frec + b->frec, a, b));
    }
    return cola.empty() ? nullptr : cola.top();
}

void generarCodigos(const Nodo* n, const std::string& actual,
                    std::map<unsigned char, std::string>& tabla) {
    if (!n) return;
    if (!n->izq && !n->der) {
        tabla[n->c] = actual.empty() ? "0" : actual;
        return;
    }
    generarCodigos(n->izq, actual + "0", tabla);
    generarCodigos(n->der, actual + "1", tabla);
}

std::string obtenerCodigo(unsigned char c,
                          const std::map<unsigned char, std::string>& tabla) {
    return tabla.at(c);
}

// Funcion del prompt: sustituye cada caracter por su codigo (std::string),
// concatena todo en un solo string y lo guarda en disco.
void comprimirIngenuo(const std::string& rutaEntrada, const std::string& rutaSalida,
                      const std::map<unsigned char, std::string>& tabla) {
    std::ifstream in(rutaEntrada, std::ios::binary);
    if (!in) {
        std::cerr << "No se pudo abrir " << rutaEntrada << "\n";
        return;
    }

    std::string resultado;
    char ch;
    while (in.get(ch))
        resultado += obtenerCodigo(static_cast<unsigned char>(ch), tabla);

    std::ofstream out(rutaSalida);
    out << resultado;
}

long long tamanioArchivo(const std::string& ruta) {
    std::ifstream f(ruta, std::ios::binary | std::ios::ate);
    return f ? static_cast<long long>(f.tellg()) : -1;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <entrada> <salida>\n";
        return 1;
    }
    std::string entrada = argv[1];
    std::string salida = argv[2];

    std::ifstream in(entrada, std::ios::binary);
    if (!in) {
        std::cerr << "No se pudo abrir " << entrada << "\n";
        return 1;
    }

    std::map<unsigned char, long long> frecuencias;
    char ch;
    while (in.get(ch))
        frecuencias[static_cast<unsigned char>(ch)]++;
    in.close();

    if (frecuencias.empty()) {
        std::cerr << "El archivo esta vacio\n";
        return 1;
    }

    Nodo* raiz = construirArbol(frecuencias);
    std::map<unsigned char, std::string> tabla;
    generarCodigos(raiz, "", tabla);

    comprimirIngenuo(entrada, salida, tabla);

    long long original = tamanioArchivo(entrada);
    long long comprimido = tamanioArchivo(salida);
    std::cout << "Tamano original:  " << original << " bytes\n";
    std::cout << "Tamano de salida: " << comprimido << " bytes\n";
    std::cout << "Salida / original: " << static_cast<double>(comprimido) / original << "\n";

    liberarArbol(raiz);
    return 0;
}
