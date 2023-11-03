#include <iostream>
#include <conio.h>
using namespace std;

void imprimir_matriz(bool** matriz, int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int main() {
	int n = 0, opcion;
	do
	{
		system("CLS");
		cout << "Ingrese el valor de n: "; cin >> n;
	} while (n < 5 || n>15);

	bool** matriz = new bool* [n];
	for (int i = 0; i < n; i++)
		matriz[i] = new bool[n];
	bool** matriz_aux = new bool* [n];
	for (int i = 0; i < n; i++)
		matriz_aux[i] = new bool[n];
	bool* verificador = new bool[n];
	bool verif;
	bool** matriz_ordenada = new bool* [n];
	for (int i = 0; i < n; i++)
		matriz_ordenada[i] = new bool[n];

	do
	{
		cout << char(168) << "Desea digitar los valores o generarlos aleatoriamente? (0= random 1= manualmente): "; cin >> opcion;
	} while (opcion != 0 && opcion != 1);
	if (opcion == 0)
	{
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matriz[i][j] = rand() % 2;
			}
		}
	}
	else
	{
		cout << "El valor debe ser 0 o 1\n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				do
				{
					cout << "Valor de (" << i << "," << j << "): "; cin >> matriz[i][j];
				} while (matriz[i][j] != 0 && matriz[i][j] != 1);

			}
		}
	}
	cout << "Matriz de adyacencia: \n\n";
	imprimir_matriz(matriz, n);

	//copiando la matriz de adyacencia en la aux
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matriz_aux[i][j] = matriz[i][j];
		}
	}

	cout << "Matriz aux:\n\n";
	imprimir_matriz(matriz_aux, n);

	//calculos

	for (int i = 0; i < n; i++) {
		do
		{
			verif = true;
			for (int d = 0; d < n; d++) { verificador[d] = matriz_aux[i][d]; }
			for (int j = 0; j < n; j++) {

				if (matriz_aux[i][j] == 1)
				{

					for (int k = 0; k < n; k++) {
						if (matriz_aux[i][k] == 0 && matriz_aux[j][k] == 1)
						{
							matriz_aux[i][k] = 1;
						}
					}
				}
			}
			for (int d = 0; d < n; d++) {
				if (verificador[d] != matriz_aux[i][d])
				{
					verif = false;
				}
			}
		} while (!verif);
	}
	cout << "Matriz de caminos: (sin la diagonal llena de 1s) \n\n";
	imprimir_matriz(matriz_aux, n);
	// Añade 1's a la diagonal de la matriz auxiliar 
	for (int i = 0; i < n; i++) {
		matriz_aux[i][i] = 1;
	}

	cout << "Matriz de caminos: (con la diagonal llena de 1s) \n\n";
	imprimir_matriz(matriz_aux, n);
	//calculos de ordenar
	int* contador = new int[n];
	for (int i = 0; i < n; i++) { contador[i] = 0; }//inicializa el vector contador en 0
	bool* vector_auxiliar = new bool[n]; //auxiliar para ordenar las filas y columnas
	int auxiliar_fila = 0; 
	int* col_aux = new int[n];
	for (int i = 0; i < n; i++) { col_aux[i] = i; } //aux futuro para las columnas se inicializa en 0,1,2,3...
	//para asi tener el orden de como poner las columnas

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matriz_ordenada[i][j] = matriz_aux[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matriz_aux[i][j]) { contador[i]++; }
		}
	}
	cout << "\nCantidad de 1s por fila: \n";
	for (int i = 0; i < n; i++) { cout << contador[i] << endl; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (contador[j] < contador[j + 1]) {
				for (int l = 0; l < n; l++) { vector_auxiliar[l] = matriz_ordenada[j][l]; }
				auxiliar_fila = contador[j];
				contador[j] = contador[j + 1];
				contador[j + 1] = auxiliar_fila;
				auxiliar_fila = col_aux[j];
				col_aux[j] = col_aux[j + 1];
				col_aux[j + 1] = auxiliar_fila;
				for (int k = 0; k < n; k++) {

					matriz_ordenada[j][k] = matriz_ordenada[j + 1][k];
					matriz_ordenada[j + 1][k] = vector_auxiliar[k];
				}
			}
		}
	}
	cout << "\nMatriz ordenada en filas: \n";
	imprimir_matriz(matriz_ordenada, n);
	cout << endl;
	bool** matriz_col_aux = new bool* [n];
	for (int i = 0; i < n; i++)
		matriz_col_aux[i] = new bool[n];

	for (int i = 0; i < n; i++) {//copiando la matriz ordenada en una matriz auxiliar 
		for (int j = 0; j < n; j++) {
			matriz_col_aux[i][j] = matriz_ordenada[i][j];
		}
	}

	for (int i = 0; i < n; i++) {//ordenando por columnas
		for (int j = 0; j < n; j++) {
			matriz_ordenada[j][i] = matriz_col_aux[j][col_aux[i]];
		}
	}

	cout << "\n\nMatriz ordenada en columnas: \n";
	for (int i = 0; i < n; i++) {
		cout << col_aux[i] + 1 << " ";
	}
	cout << endl;
	imprimir_matriz(matriz_ordenada, n);

	//componentes conexas

	bool contar_conexas = true;
	int cantidad_unos = 0;
	int auxiliar_unos;
	int cantidadconexas = 0;
	int x = 0;
	do {
		for (int i = x; i < n; i++) {
			contar_conexas = true;
			cantidad_unos = 0;
			for (int j = x; j < n; j++) {
				if (matriz_ordenada[j][i] == 1 && contar_conexas == true) {
					cantidad_unos++;
				}
				else {
					contar_conexas = false;
				}
			}
			if (i != x && cantidad_unos > auxiliar_unos) { cantidadconexas++; break; }
			auxiliar_unos = cantidad_unos;
		}
		//cout << auxiliar_unos << " ";
		cout << "La componente conexa " << cantidadconexas << " inicia en [" << x << "][" << x << "] hasta ";
		x += auxiliar_unos;
		cout << "[" << x - 1 << "]" << "[" << x - 1 << "]" << endl;
	} while (x < n);

	for (int i = 0; i < n; i++) {
		delete[] matriz[i];
	}
	delete[] matriz;
	for (int i = 0; i < n; i++) {
		delete[] matriz_aux[i];
	}
	delete[] matriz_aux;
	for (int i = 0; i < n; i++) {
		delete[] matriz_ordenada[i];
	}
	delete[] matriz_ordenada;
	for (int i = 0; i < n; i++) {
		delete[] matriz_col_aux[i];
	}
	delete[] matriz_col_aux;
	system("pause");
}
