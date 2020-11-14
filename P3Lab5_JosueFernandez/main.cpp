/* Laboratorio #5, Programación 3
 * Josué Fernández, 12011228.
 */

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::stringstream;

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
int** multiplicarMatrices(int** m1, int nFilas, int nCol, int** m2, int nnFilas, int nnCol);
void operar(string operaciones);

int main(int argc, char** argv) {

    srand(time(0));

    int cantidadActual = 0;

    int opcion = 0;
    string operaciones = "";
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
                cantidadActual = vectorSize;

                operaciones = "";
                cout << "Ingrese las operaciones a realizar: ";
                cin >> operaciones;

                operar(operaciones);
                for (int i = cantidadActual; i < vectorSize; i++) {
                    int** matriz = lista.at(i);
                    liberarMatriz(matriz, filas.at(i));
                }

                lista.erase(lista.begin() + cantidadActual, lista.end());
                lista.shrink_to_fit();

                filas.erase(filas.begin() + cantidadActual, filas.end());
                filas.shrink_to_fit();

                columnas.erase(columnas.begin() + cantidadActual, columnas.end());
                columnas.shrink_to_fit();

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

int** multiplicarMatrices(int** m1, int nFilas, int nCol,
        int** m2, int nnFilas, int nnCol) {
    if (nCol != nnFilas) {
        return NULL;
    }
    int** nueva = new int*[nFilas];
    for (int i = 0; i < nFilas; i++) {
        nueva[i] = new int[nnCol];
        for (int j = 0; j < nnCol; j++) {
            nueva[i][j] = 0;
            for (int k = 0; k < nCol; k++) {
                nueva[i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }

    //Agregamos la nueva matriz a la lista
    //    lista.push_back(nueva);
    //    filas.push_back(nFilas);
    //    columnas.push_back(nnCol);
    //    vectorSize++;

    return nueva;
}

int contar(string cadena, char caracter) {
    int contador = 0;

    for (int i = 0; i < cadena.length(); i++) {
        if (cadena[i] == caracter) {
            contador++;
        }
    }

    return contador;
}

int** sumarMatrices(int** m1, int nFilas, int nCol,
        int** m2, int nnFilas, int nnCol) {

    if (nFilas != nnFilas || nCol != nnCol) {
        return NULL;
    }

    int** nueva = new int*[nFilas];
    for (int i = 0; i < nFilas; i++) {
        nueva[i] = new int[nCol];
        for (int j = 0; j < nCol; j++) {
            nueva[i][j] = (m1[i][j] + m2[i][j]);
        }
    }

    //Agregamos la nueva matriz a la lista
    //    lista.push_back(nueva);
    //    filas.push_back(nFilas);
    //    columnas.push_back(nnCol);
    //    vectorSize++;

    return nueva;
}

int** restarMatrices(int** m1, int nFilas, int nCol,
        int** m2, int nnFilas, int nnCol) {

    if (nFilas != nnFilas || nCol != nnCol) {
        return NULL;
    }

    int** nueva = new int*[nFilas];
    for (int i = 0; i < nFilas; i++) {
        nueva[i] = new int[nCol];
        for (int j = 0; j < nCol; j++) {
            nueva[i][j] = (m1[i][j] - m2[i][j]);
        }
    }

    //Agregamos la nueva matriz a la lista
    //    lista.push_back(nueva);
    //    filas.push_back(nFilas);
    //    columnas.push_back(nnCol);
    //    vectorSize++;

    return nueva;
}

int** multiplicacionRecursiva(vector<int> numeros, int sizeNum, int i) {

    if (sizeNum < 2 || i > sizeNum - 2) {
        cout << "ERRRRRRRRRRRRRRRRRRRRRRRRORRRRRRRRRRRRRRRRRRR " << sizeNum << endl;
        return NULL;
    } else if (i == sizeNum - 2) {
        return multiplicarMatrices(lista.at(numeros.at(sizeNum - 2)), filas.at(numeros.at(sizeNum - 2)), columnas.at(numeros.at(sizeNum - 2)),
                lista.at(numeros.at(sizeNum - 1)), filas.at(numeros.at(sizeNum - 1)), columnas.at(numeros.at(sizeNum - 1)));
    } else {
        return multiplicarMatrices(lista.at(numeros.at(i)), filas.at(numeros.at(i)), columnas.at(numeros.at(i)),
                multiplicacionRecursiva(numeros, sizeNum, i + 1), filas.at(numeros.at(i + 1)), columnas.at(numeros.at(sizeNum - 1)));
    }
}

void operar(string operaciones) {
    string nueva = "";

    int sizeOp = 0;
    vector <char> operadores;

    int sizeTer = 0;
    vector <string> terminos;



    //string auxiliar;
    int ultimo = 0;
    for (int i = 0; i < operaciones.length(); i++) {
        if (operaciones[i] == '+' || operaciones[i] == '-') {

            operadores.push_back(operaciones[i]);
            sizeOp++;

            terminos.push_back(operaciones.substr(ultimo, i));
            ultimo = i + 1;
            sizeTer++;
        }
    }
    terminos.push_back(operaciones.substr(ultimo));
    sizeTer++;


    for (int i = 0; i < sizeTer; i++) {

        string termino = terminos.at(i);
        int cantidad = contar(termino, '*');


        //Si hay alguna multiplicacion
        if (cantidad > 0) {
            int sizeNum = 0;
            vector <int> numeros;
            stringstream ss(termino);
            string item;

            while (getline(ss, item, '*')) {
                int num = stoi(item, nullptr, 10);
                numeros.push_back(num);
                sizeNum++;
            }

            int ** producto = multiplicacionRecursiva(numeros, sizeNum, 0);

            //Agregamos la nueva matriz a la lista
            lista.push_back(producto);
            filas.push_back(filas.at(numeros.at(0)));
            columnas.push_back(columnas.at(numeros.at(sizeNum - 1)));
            vectorSize++;

            terminos[i] = to_string(vectorSize - 1);

        }
    }

    //Sumas y restas
    int ** matriz = lista.at(stoi(terminos[0], nullptr, 10));
    int fil = filas.at(stoi(terminos[0], nullptr, 10));
    ;
    int col = columnas.at(stoi(terminos[0], nullptr, 10));
    ;

    for (int i = 0; i < sizeOp; i++) {

        int ** auxiliar;
        if (operadores[i] == '+') {
            auxiliar = sumarMatrices(matriz, fil, col,
                    lista.at(stoi(terminos[i + 1], nullptr, 10)), 
                    filas.at(stoi(terminos[i + 1], nullptr, 10)), 
                    columnas[stoi(terminos[i + 1], nullptr, 10)]);
        } else {
            auxiliar = restarMatrices(matriz, fil, col,
                    lista.at(stoi(terminos[i + 1], nullptr, 10)), 
                    filas.at(stoi(terminos[i + 1], nullptr, 10)), 
                    columnas[stoi(terminos[i + 1], nullptr, 10)]);
        }
        if (auxiliar == NULL) {
            cout << "No se pudo realizar la operacion" << endl;
            return;
        }
        liberarMatriz(matriz, fil);
        matriz = auxiliar;
    }

    imprimirMatriz(matriz, fil, col);

}


