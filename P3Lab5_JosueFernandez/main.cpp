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
vector <int**> lista;
vector <int> filas;
vector <int> columnas;

//Prototipos

//Muestra las opciones y retorna la elegida por el usuario
int menu();
//Genera una matriz con numeros aleatorios entre -50 y 50
void generarMatriz(int nFilas, int nColumnas);
//Pide al usuario que ingrese los numeros de la matriz
void pedirMatriz(int nFilas, int nColumnas);
//Libera la matriz
void liberarMatriz(int**& matriz, int nFilas);
//Imprime la matriz
void imprimirMatriz(int ** matriz, int nFilas, int nCol);
//Multiplica dos matrices (si es posible) y las añade al vector de matrices
bool multiplicarMatrices(int** m1, int nFilas, int nCol, int** m2, int nnFilas, int nnCol);
//Retorna el producto punto de dos arreglos
int productoPunto(int* arr1, int* arr2, int size);

int main(int argc, char** argv) {

    srand(time(0));

    int opcion = 0;

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
                    pedirMatriz(nFilas, nColumnas);
                } else {
                    generarMatriz(nFilas, nColumnas);
                }

                imprimirMatriz(lista.at(vectorSize - 1), nFilas, nColumnas);
                cout << endl;

                break;
            case 3:
                
                cout << "Multiplicando 0 y 1 " << endl;
                
                if(multiplicarMatrices(lista.at(0), filas.at(0), columnas.at(0), lista.at(1), filas.at(1), columnas.at(1))){
                    imprimirMatriz(lista.at(vectorSize-1),filas.at(vectorSize-1), columnas.at(vectorSize-1));
                }
                
                break;
            case 4:

                break;
            default:
                cout << "Ingreso una opcion invalida." << endl;
                break;
        }

    } while (opcion != 4);

    //reverse_iterator<> ri = lista.rbegin();

    for (int i = 0; i < vectorSize; i++) {
        int** matriz = lista.at(i);
        liberarMatriz(matriz, filas.at(i));
    }

    lista.erase(lista.begin(), lista.end());
    lista.shrink_to_fit();

    filas.erase(filas.begin(), filas.end());
    filas.shrink_to_fit();

    columnas.erase(columnas.begin(), columnas.end());
    columnas.shrink_to_fit();

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

void generarMatriz(int nFilas, int nColumnas) {
    if (nFilas > 0 && nColumnas > 0) {
        int** mat = new int*[nFilas];
        for (int i = 0; i < nFilas; i++) {
            mat[i] = new int[nColumnas];
            for (int j = 0; j < nColumnas; j++) {
                mat[i][j] = (-50 + rand() % 101);
            }
        }
        lista.push_back(mat);
        filas.push_back(nFilas);
        columnas.push_back(nColumnas);
        vectorSize++;
    }
}

void pedirMatriz(int nFilas, int nColumnas) {
    if (nFilas > 0 && nColumnas > 0) {
        int** mat = new int*[nFilas];
        for (int i = 0; i < nFilas; i++) {
            mat[i] = new int[nColumnas];
            for (int j = 0; j < nColumnas; j++) {
                cout << "Ingrese el valor de la matriz en [" << i << "][" << j << "]: ";
                cin >> mat[i][j];
            }
        }
        lista.push_back(mat);
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

bool multiplicarMatrices(int** m1, int nFilas, int nCol, 
                         int** m2, int nnFilas, int nnCol) {
    if (nCol != nnFilas) {
        return false;
    }
    int** nueva = new int*[nFilas];
    for (int i = 0; i < nFilas; i++) {
        nueva[i] = new int[nnCol];
        for (int j = 0; j < nnCol; j++) {
            nueva[i][j] = 0;
            for (int k = 0; k < nCol; k++) {
                nueva[i][j] += (m1[i][k] * m2[k][i]);
            }
        }
    }

    //Agregamos la nueva matriz a la lista
    lista.push_back(nueva);
    filas.push_back(nFilas);
    columnas.push_back(nnCol);
    vectorSize++;

    return true;
}