#include "stdafx.h"
#include "Kernel.h";
#include <iostream>
#include <string>
using namespace std;

int accion = 0;
int ventana;
int existe = 0;
#pragma region variables
#define add 1
#define remove 2
#define quantum 3
#define si 1
#pragma endregion

void menu(){
	cout << "\n" << "Que desea hacer? " << "\n";
	cout << "1. Add" << ".\n" << "2. Remove" << ".\n" << "3. quantum" << ".\n" << "4. Salir ";
	cin >> accion;
}
int verificarexistencia() {
	if (existe != si)
	{
		cout << "No hay ventanas creadas";
		menu();
	}
	return existe;
}

int main()
{
	Kernel *k = new Kernel();

	while (accion != 4)
	{
		menu();
		switch (accion)
		{
		case add:
			cout << "Ingrese el numero de ventana: ";
			cin >> ventana;
			k->addprocess(ventana);
			cout << "El proceso fue agregado";
			cin.ignore();
			existe = si;
			break;
		case remove:
			verificarexistencia();
			cout << "Ingrese el numero de ventana: ";
			cin >> ventana;
			cin.ignore();
			break;

		case quantum:
			verificarexistencia();
			cout << "Ingrese el numero de ventana: ";
			cin >> ventana;
			cout << "Ingrese el valor del Quantum: ";
			int iquantum;
			cin >> iquantum;
			k->changequantum(ventana, iquantum);
			cin.ignore();

			break;
		}
	}
}



