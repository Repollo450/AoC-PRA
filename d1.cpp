#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

std::vector<int> listaIzquierda = {0};
std::vector<int> listaDerecha = {0};

using namespace std;

void cargarArchivo(const char* rutaArchivo) {
    FILE* archivo = fopen(rutaArchivo, "r");
    if (!archivo) {
        cerr << "Error: No se pudo abrir el archivo.\n";
        exit(EXIT_FAILURE);
    }
    int valor1, valor2;
    while (fscanf(archivo, "%d %d", &valor1, &valor2) != EOF) {
        listaIzquierda.push_back(valor1);
        listaDerecha.push_back(valor2);
    }
    fclose(archivo);
}

void ordenarVector(vector<int>& vector) {
    int tamano = vector.size();
    for (int i = 0; i < tamano - 1; ++i) {
        for (int j = 0; j < tamano - i - 1; ++j) {
            if (vector[j] > vector[j + 1]) {
                swap(vector[j], vector[j + 1]);
            }
        }
    }
}

unsigned long long calcularSumaDeDiferencias(const vector<int>& vectorA, const vector<int>& vectorB) {
    unsigned long long sumaDiferencias = 0;
    int tamano = vectorA.size();
    for (int i = 0; i < tamano; ++i) {
        sumaDiferencias += abs(vectorA[i] - vectorB[i]);
    }
    return sumaDiferencias;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <ruta_archivo>\n";
        return EXIT_FAILURE;
    }

    const char* rutaArchivo = argv[1];
    cargarArchivo(rutaArchivo);
    ordenarVector(listaIzquierda);
    ordenarVector(listaDerecha);
    cout << calcularSumaDeDiferencias(listaIzquierda, listaDerecha) << endl;

    return 0;
}
