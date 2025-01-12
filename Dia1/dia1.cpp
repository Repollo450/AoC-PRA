#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Implementación del ordenamiento por inserción
void ordenarPorInsercion(int* datos, int longitud) {
    for (int i = 1; i < longitud; i++) { // Iterar desde el segundo elemento
        int elementoActual = datos[i]; // Almacenar el elemento actual
        int posicion = i - 1; // Índice para comparación

        // Desplazar elementos mayores hacia adelante
        while (posicion >= 0 && datos[posicion] > elementoActual) {
            datos[posicion + 1] = datos[posicion];
            posicion--;
        }

        // Insertar el elemento en su lugar adecuado
        datos[posicion + 1] = elementoActual;
    }
}

int main() {
    ifstream archivoEntrada("input.txt");
    string lineaLeida;

    int totalLineas = 0;

    // Contar el número de líneas en el archivo
    while (getline(archivoEntrada, lineaLeida)) {
        totalLineas++;
    }

    archivoEntrada.close();
    archivoEntrada.open("input.txt");

    // Crear arreglos dinámicos para almacenar los números
    int* listaPrimaria = new int[totalLineas];
    int* listaSecundaria = new int[totalLineas];

    int contador = 0;
    while (getline(archivoEntrada, lineaLeida)) {
        int numeroA, numeroB;
        sscanf(lineaLeida.c_str(), "%d %d", &numeroA, &numeroB);
        listaPrimaria[contador] = numeroA;
        listaSecundaria[contador] = numeroB;
        contador++;
    }

    archivoEntrada.close();

    // Ordenar ambos arreglos
    ordenarPorInsercion(listaPrimaria, totalLineas);
    ordenarPorInsercion(listaSecundaria, totalLineas);

    // Calcular la suma de diferencias absolutas
    int sumaDiferencias = 0;
    for (int i = 0; i < totalLineas; i++) {
        int diferenciaAbsoluta = abs(listaPrimaria[i] - listaSecundaria[i]);
        sumaDiferencias += diferenciaAbsoluta;
    }

    cout << "Suma total de diferencias: " << sumaDiferencias << endl;

    // Liberar la memoria dinámica
    delete[] listaPrimaria;
    delete[] listaSecundaria;

    return 0;
} 
