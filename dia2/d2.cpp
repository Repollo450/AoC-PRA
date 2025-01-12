#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

// Función para verificar si una secuencia de números es válida
bool es_segura(const std::vector<int>& numeros) {
    if (numeros.size() < 2) return false; // No hay suficientes elementos para analizar

    int direccionInicial = (numeros[1] > numeros[0]) ? 1 : -1; // Determina si es ascendente o descendente
    for (size_t i = 0; i < numeros.size() - 1; ++i) {
        int diferencia = numeros[i + 1] - numeros[i];
        if (std::abs(diferencia) < 1 || std::abs(diferencia) > 3) return false; // Diferencia no válida
        if ((diferencia > 0 && direccionInicial < 0) || (diferencia < 0 && direccionInicial > 0)) return false; // Cambio de dirección
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo>" << std::endl;
        return 1;
    }

    std::ifstream archivo(argv[1]);
    if (!archivo) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    int contadorSeguras = 0;
    std::string linea;

    // Leer cada línea del archivo
    while (std::getline(archivo, linea)) {
        std::istringstream flujo(linea);
        std::vector<int> numeros;
        int numero;

        // Extraer números de la línea
        while (flujo >> numero) {
            numeros.push_back(numero);
        }

        // Verificar si la línea cumple las condiciones de seguridad
        if (es_segura(numeros)) {
            ++contadorSeguras;
        }
    }

    std::cout << "Líneas seguras: " << contadorSeguras << std::endl;
    return 0;
}
