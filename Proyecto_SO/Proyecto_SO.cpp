#include "stdafx.h"
#include "Kernel.h";
#include <iostream>
#include <string>
using namespace std;

int accion = 0;
int ventana = 0;
int procesos = 0;

Kernel *k = new Kernel();
#pragma region variables
#define add 1
#define remove 2
#define quantum 3
#define salir 4
#pragma endregion



void menu() {
	cout << "\n" << "Que desea hacer? " << "\n";
	cout << "1. Add" << ".\n" << "2. Remove" << ".\n" << "3. quantum" << ".\n" << "4. Salir ";
	cin >> accion;
}

bool verificarexistencia() {
	if (procesos == 0)
	{
		cout << "No hay ventanas creadas" << "\n";
		menu();
		return false;
	}
	return true;
}

bool verificarventana() {

}

void acciones() {
	switch (accion)
	{
	case add:
		if (procesos !=6)
		{
			cout << "Ingrese el numero de ventana: ";
			cin >> ventana;
			k->addprocess(ventana);
			cout << "El proceso fue agregado";
			procesos++;
			cin.ignore();
			menu();
		}
		break;
	case remove:
		if (verificarexistencia() == true)
		{
			cout << "Ingrese el numero de ventana: ";
			cin >> ventana;
			procesos--;
			cin.ignore();
			menu();
		}
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
		menu();
		break;
	case salir:
		break;
	}
}

int main()
{
	menu();
	while (accion != 4)
	{
		acciones();
	}
}



