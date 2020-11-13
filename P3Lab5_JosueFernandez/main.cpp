/* Laboratorio #5, Programación 3
 * Josué Fernández, 12011228.
 */

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using std::endl;
using std::cout;
using std::cin;
using std::vector;

using namespace std;

int vectorSize = 0;

//Prototipos

//Muestra las opciones y retorna la elegida por el usuario
int menu();
//Genera una matriz con numeros aleatorios entre -50 y 50
void generarMatriz(int nFilas, int nColumnas, vector <int**>& matrices, vector <int>& filas, vector <int>& columnas);
//Pide al usuario que ingrese los numeros de la matriz
void pedirMatriz(int nFilas, int nColumnas, vector<int**>& matrices, vector <int>& filas, vector <int>& columnas);
//Libera la matriz
void liberarMatriz(int**& matriz, int nFilas);
//Imprime la matriz
void imprimirMatriz(int ** matriz, int nFilas, int nCol);

int main(int argc, char** argv) {

    srand(time(0));

    int opcion = 0;
    vector <int**> lista;
    vector <int> filas;
    vector <int> columnas;

    filas.push_back(14);

    do {

        int nFilas = 0, nColumnas = 0;

        switch (opcion = menu()) {
            case 1:
            case 2:
                cout << "Ingrese las filas: ";
                cin >> nFilas;
                while (nFilas < 1) {
                    cout << "Ingrese las filas (debe ser mayor a 0): ";
                    cin >> nFilas;
                }

                cout << "Ingrese las columnas: ";
                cin >> nColumnas;
                while (nColumnas < 1) {
                    cout << "Ingrese las columnas (debe ser mayor a 0): ";
                    cin >> nColumnas;
                }

                if (opcion == 1) {
                    pedirMatriz(nFilas, nColumnas, lista, filas, columnas);
                } else {
                    generarMatriz(nFilas, nColumnas, lista, filas, columnas);
                }

                imprimirMatriz(lista.at(vectorSize - 1), nFilas, nColumnas);
                cout << endl;

                break;
            case 3:

                break;
            case 4:

                break;
            default:
                cout << "Ingreso una opcion invalida." << endl;
                break;
        }

    } while (opcion != 4);

    cout << "\nSalio con " << vectorSize;


    while(lista.rbegin()) { // int i = vectorSize - 1; i > 0; i--
        cout << "\n\tVuelta #" << vectorSize--;
        int** matriz = lista.at(vectorSize);
        cout << "\nRecibio la referencia";
        liberarMatriz(matriz, filas.at(vectorSize));
        cout << "\nLibero la matriz";
        lista.pop_back();
        cout << "\nHizo pop_back la lista";
        filas.pop_back();
        cout << "\nHizo pop_back las filas";
        columnas.pop_back();
        cout << "\nHizo pop_back las columnas";
    }

    cout << "\nTermino";

    return 0;
}

//Muestra las opciones y retorna la elegida por el usuario

int menu() {
    int opcion = 0;

    cout << "\t\tMENU" << endl
            << "1. Ingresar matriz" << endl
            << "2. Generar matriz" << endl
            << "3. Realizar operacion entre matrices" << endl
            << "4. Salir" << endl;
    do {
        cout << "Ingrese una opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > 4);
    cout << endl;
    return opcion;
}

void generarMatriz(int nFilas, int nColumnas, vector <int**>& matrices, vector <int>& filas, vector <int>& columnas) {
    if (nFilas > 0 && nColumnas > 0) {
        int** mat = new int*[nFilas];
        for (int i = 0; i < nFilas; i++) {
            mat[i] = new int[nColumnas];
            for (int j = 0; j < nColumnas; j++) {
                mat[i][j] = (-50 + rand() % 101);
            }
        }
        matrices.push_back(mat);
        filas.push_back(nFilas);
        columnas.push_back(nColumnas);
        vectorSize++;
    }
}

void pedirMatriz(int nFilas, int nColumnas, vector<int**>& matrices, vector <int>& filas, vector <int>& columnas) {
    if (nFilas > 0 && nColumnas > 0) {
        int** mat = new int*[nFilas];
        for (int i = 0; i < nFilas; i++) {
            mat[i] = new int[nColumnas];
            for (int j = 0; j < nColumnas; j++) {
                cout << "Ingrese el valor de la matriz en [" << i << "][" << j << "]: ";
                cin >> mat[i][j];
            }
        }
        matrices.push_back(mat);
        filas.push_back(nFilas);
        columnas.push_back(nColumnas);
        vectorSize++;
    }
}

void liberarMatriz(int**& matriz, int nFilas) {
    if (matriz != NULL && nFilas > 0) {
        for (int i = 0; i < nFilas; i++) {
            if (matriz[i] != NULL) {
                delete [] matriz[i];
                matriz[i] = NULL;
            }
        }
        delete [] matriz;
        matriz = NULL;
    }
}

void imprimirMatriz(int ** matriz, int nFilas, int nCol) {
    if (matriz != NULL && nFilas > 0 && nCol > 0) {
        for (int i = 0; i < nFilas; i++) {
            for (int j = 0; j < nCol; j++) {
                cout << matriz[i][j] << "\t";
            }
            cout << endl;
        }
    }
}