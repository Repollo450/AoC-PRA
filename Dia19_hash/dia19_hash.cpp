#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// Constantes
#define TABLE_SIZE 97  // Tamaño de la tabla hash (un número primo para reducir colisiones)
#define EMPTY ""       // Indica una posición vacía en la tabla hash

// Función hash simple
inline int hash(const std::string& key) {
    int h = 0;
    for (char c : key) h = (h * 31 + c) % TABLE_SIZE;
    return h;
}

// Función para imprimir la tabla hash
void print(const unordered_set<string>& patronesSet) {
    cout << "Tabla Hash:\n";
    for (const auto& pattern : patronesSet) {
        cout << pattern << " ";
    }
    cout << endl;
}

// Inserta un patrón en la tabla hash
void insert(const std::string& pattern, unordered_set<string>& patronesSet) {
    patronesSet.insert(pattern);
}

// Función para leer patrones y diseños desde un archivo
void leerdata(vector<string>& patrones, vector<string>& disenos) {
    ifstream file("input.txt");
    string line;
    bool lecturaPatrones = true;

    while (getline(file, line)) {
        if (line.empty()) {
            lecturaPatrones = false;
            continue;
        }

        if (lecturaPatrones) {
            stringstream ss(line);
            string patron;
            while (getline(ss, patron, ',')) {
                patron.erase(0, patron.find_first_not_of(" \t\n\r\f\v")); // strip
                patrones.push_back(patron);
            }
        } else {
            disenos.push_back(line);
        }
    }
}

// Función para comprobar si un diseño puede ser formado usando los patrones
bool comprobarPatrones(const string& diseno, const unordered_set<string>& patronesSet, vector<int>& mem) {
    if (diseno.empty())
        return true;

    int n = diseno.size();
    if (mem[n] != -1)
        return mem[n];

    for (const auto& patron : patronesSet) {
        if (diseno.find(patron) == 0) {
            if (comprobarPatrones(diseno.substr(patron.length()), patronesSet, mem)) {
                mem[n] = 1;
                return true;
            }
        }
    }

    mem[n] = 0;
    return false;
}

int main() {
    vector<string> patrones;
    vector<string> disenos;
    int sum = 0;

    leerdata(patrones, disenos);

    // Insertar patrones en una tabla hash
    unordered_set<string> patronesSet;
    for (const auto& pattern : patrones) {
        insert(pattern, patronesSet);
    }

#ifdef DEBUG
    print(patronesSet); // Imprimir la tabla hash para depuración
#endif

    for (const auto& diseno : disenos) {
        vector<int> mem(diseno.size() + 1, -1);
        if (comprobarPatrones(diseno, patronesSet, mem)) {
            sum++;
        }
    }

    cout << "Número total de combinaciones de patrones: " << sum << endl;
    return 0;
}