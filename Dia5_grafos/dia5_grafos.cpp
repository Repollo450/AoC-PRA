#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <fstream>
using namespace std;

void imprimirGrafo(const unordered_map<int, vector<int>> &grafo) {
    for (const auto &par : grafo) {
        cout << par.first << ":\t";
        for (const int &val : par.second) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Se lee el archivo input5.txt, separando su contenido en dos partes: las reglas de orden de las páginas y las actualizaciones de páginas. Luego, almacena estos datos en dos estructuras diferentes (lectura y orden)
void insertar(unordered_map<int, vector<int>> &lectura, vector<vector<int>> &orden) {
    bool espacio = false;
    string input, inputX, inputY, nextInput;
    int x, y;
    ifstream file("input5.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo input5.txt" << endl;
        exit(EXIT_FAILURE);
    }
    // Se lee el archivo línea por línea y se comprueba que el formato del archivo input5.txt es el correcto. Se separan las dos partes del archivo.
    while (getline(file, input)) {
        if (input.empty()) {
            espacio = true;
            continue;
        }

        // Se procesa la segunda sección del archivo, que contiene los números de página de cada actualización.
        if (espacio) {
            vector<int> num;
            stringstream entrada(input);
            while (getline(entrada, nextInput, ',')) {
                num.push_back(stoi(nextInput));
            }
            orden.push_back(num);
        // Se procesa la primera sección del archivo, que contiene las reglas de orden de las páginas.
        } else {
            // El inputX es el valor que aparece antes de '|' y el inputY es el valor que aparece después.
            // Se añade al final del vector el segundo valor. En el caso de que no exista, se crea.
            stringstream entrada(input);
            getline(entrada, inputX, '|');
            getline(entrada, inputY);
            x = stoi(inputX); 
            y = stoi(inputY);
            lectura[x].push_back(y);
        }
    }
    file.close();
}

//Se utiliza para obtener el número de página central de cada actualización correctamente ordenada, y sumar estos números para obtener un resultado final.
int mitad(vector<int> &orden) {
    return orden[orden.size() / 2];
}

//Se comprueba si cada par de páginas x|y aparece en el orden adecuado (x antes que y)
bool validar(unordered_map<int, vector<int>> &lectura, vector<int> &orden) {
    int norden = orden.size();
    for (int i = 0; i < orden.size(); i++) {
        if (lectura.find(orden[i]) == lectura.end()) {
            continue;
        }
        vector<int> &valores = lectura[orden[i]];
        for (int j = i + 1; j < norden; j++) {
            bool encontrado = false;
            for (int x = 0; x < valores.size(); x++) {
                if (orden[j] == valores[x]) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    unordered_map<int, vector<int>> lectura;
    vector<vector<int>> orden;
    int sumaMitades = 0;

    insertar(lectura, orden);

    imprimirGrafo(lectura);

    for (int i = 0; i < orden.size(); i++) {
        if (validar(lectura, orden[i])) {
            sumaMitades += mitad(orden[i]);
        }
    }

    cout << "La suma de todas las mitades es: " << sumaMitades << endl;

    return 0;
}