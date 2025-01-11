#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

struct NodoArbol {
    int valor;
    NodoArbol *hijoDerecho;
    NodoArbol *hijoIzquierdo;
};

NodoArbol *crearNodoArbol(int);
void insertarEnArbol(NodoArbol*&, int);
int calcularSuma(NodoArbol*);
bool validarNumero(const string&);
void procesarOperaciones(ifstream&, NodoArbol*&);

const int MAX_OPERACIONES_PERMITIDAS = 100;

NodoArbol *crearNodoArbol(int numero) {
    NodoArbol *nuevoNodo = new NodoArbol();
    nuevoNodo->valor = numero;
    nuevoNodo->hijoDerecho = nullptr;
    nuevoNodo->hijoIzquierdo = nullptr;
    return nuevoNodo;
}

void insertarEnArbol(NodoArbol*& arbol, int numero) {
    if (arbol == nullptr) {
        arbol = crearNodoArbol(numero);
    } else {
        if (numero < arbol->valor) {
            insertarEnArbol(arbol->hijoIzquierdo, numero);
        } else {
            insertarEnArbol(arbol->hijoDerecho, numero);
        }
    }
}

int calcularSuma(NodoArbol* arbol) {
    if (arbol == nullptr) {
        return 0;
    }
    return arbol->valor + calcularSuma(arbol->hijoIzquierdo) + calcularSuma(arbol->hijoDerecho);
}

bool validarNumero(const string& texto) {
    if (texto.empty()) return false;

    size_t indice = 0;
    if (texto[0] == '-') indice++;

    for (; indice < texto.size(); ++indice) {
        if (!isdigit(texto[indice])) return false;
    }

    return true;
}

void procesarOperaciones(ifstream& archivoEntrada, NodoArbol*& arbol) {
    string linea;
    while (getline(archivoEntrada, linea)) {
        size_t posicionActual = 0;
        while ((posicionActual = linea.find("mul(", posicionActual)) != string::npos) {
            size_t inicio = posicionActual + 4;
            size_t coma = linea.find(',', inicio);
            size_t fin = linea.find(')', inicio);

            if (coma != string::npos && fin != string::npos && coma < fin) {
                string primerNumero = linea.substr(inicio, coma - inicio);
                string segundoNumero = linea.substr(coma + 1, fin - coma - 1);

                if (validarNumero(primerNumero) && validarNumero(segundoNumero)) {
                    try {
                        int numero1 = stoi(primerNumero);
                        int numero2 = stoi(segundoNumero);
                        int producto = numero1 * numero2;
                        insertarEnArbol(arbol, producto);
                    } catch (const invalid_argument& e) {
                        cerr << "Error: Argumento no válido en la conversión a entero." << endl;
                    } catch (const out_of_range& e) {
                        cerr << "Error: Número fuera de rango durante la conversión." << endl;
                    }
                }
            }
            posicionActual += 4;
        }
    }
}

int main() {
    ifstream archivoEntrada("datos_input.txt");
    if (!archivoEntrada.is_open()) {
        cerr << "Error: No se pudo abrir el archivo especificado." << endl;
        return 1;
    }

    NodoArbol *arbolPrincipal = nullptr;

    procesarOperaciones(archivoEntrada, arbolPrincipal);

    int sumaFinal = calcularSuma(arbolPrincipal);
    cout << "Resultado de la suma: " << sumaFinal << endl;

    archivoEntrada.close();
    return 0;
}
