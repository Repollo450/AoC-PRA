#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

// Función para pasar los datos del input a un vector 
// Lee el archivo "input11.txt" y almacena los números en el vector v1
void Input(vector<long long> &v1)
{
    ifstream file("input11.txt");
    string linea;

    // Lee la primera línea del archivo
    if (getline(file, linea)) {
        stringstream iss(linea);
        long long num;
        // Extrae los números de la línea y los añade al vector
        while (iss >> num) {
            v1.push_back(num);
        }
    }
    file.close();
}

// Función implementada con programación dinámica mediante una variable de memoria y recursividad. También se usa DyV.
// Calcula el número de predicciones basado en el número inicial y el número de parpadeos
int predicciones(long long numero, int parpadeos, unordered_map<string, int> &M) {
    // Caso base: si no quedan parpadeos, retorna 1
    if (parpadeos == 0) 
    return 1;

    // Crea una clave única para el estado actual
    stringstream ss;
    ss << numero << ":" << parpadeos;  
    string key = ss.str();

    // Si el resultado ya está en la memoria, lo devuelve
    if (M.find(key) != M.end()) 
    return M[key];

    int resultado = 0;

    // Si el número es 0, cambia a 1 y reduce los parpadeos
    if (numero == 0) {
        resultado = predicciones(1, parpadeos - 1, M);
    } else {
        string numStr = to_string(numero);
        // Si el número tiene una cantidad par de dígitos, se usa divide y vencerás.
        if (numStr.size() % 2 == 0) {
            resultado = predicciones(stoi(numStr.substr(0, numStr.size() / 2)), parpadeos - 1, M) + predicciones(stoi(numStr.substr(numStr.size() / 2)), parpadeos - 1, M);
        } else {
            // Si el número tiene una cantidad impar de dígitos, multiplica por 2024
            resultado = predicciones(numero * 2024, parpadeos - 1, M);
        }
    }

    // Almacena el resultado en la memoria antes de devolverlo
    M[key] = resultado; 
    return resultado;
}

int main() {
    vector<long long> registro;
    // Lee los datos de entrada
    Input(registro);
    int num = registro.size();
    int parpadeos = 25; 
    unordered_map<string, int> M;

    int total = 0;

    // Calcula el total de predicciones para cada número en el registro
    for (int i = 0; i < num; i++) {
        total += predicciones(registro[i], parpadeos, M);
    }

    // Imprime el resultado total
    cout << "Total de piedras tras " << parpadeos << " parpadeos: " << total << endl;

    return 0;
}