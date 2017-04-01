#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int accion = 0;
int ventana = 0;
int procesos = 0;
vector<string> tokens; // Create vector to hold our words

bool v1, v2, v3, v4, v5, v6 = false;

Kernel *k = new Kernel();
#pragma region variables
#define add 1
#define remove 2
#define quantum 3
#define pause 4
#define clear 5
#define stats 6
#define salir 7
#pragma endregion

int tipo(string tipo) {
	if (tipo == "add")
	{

		return add;
	}
	if (tipo == "remove")
	{
		return remove;
	}
	if (tipo == "pause")
	{
		return pause;
	}
	if (tipo == "quantum")
	{
		return quantum;
	}
	if (tipo == "clear")
	{
		return clear;
	}
	if (tipo == "stats")
	{
		return stats;
	}
	if (tipo == "salir")
	{
		return salir;
	}
}

bool verificarexistencia() {
	if (procesos == 0)
	{
		cout << "No hay ventanas creadas" << "\n";
		return false;
	}
	return true;
}

bool verificarventana() {
	bool creado = false;
	switch (ventana)
	{
	case 1:
		if (v1 == false)
		{
			v1 = true;
		}
		else
		{
			cout << "Ventana ya creada" << "\n";
			creado = true;
		}
		break;
	case 2:
		if (v2 == false)
		{
			v2 = true;
		}
		else
		{
			cout << "Ventana ya creada" << "\n";
			creado = true;
		}
		break;
	case 3:
		if (v3 == false)
		{
			v3 = true;
		}
		else
		{
			cout << "Ventana ya creada" << "\n";
			creado = true;
		}
		break;
	case 4:
		if (v4 == false)
		{
			v4 = true;
		}
		else
		{
			cout << "Ventana ya creada" << "\n";
			creado = true;
		}
		break;
	case 5:
		if (v5 == false)
		{
			v5 = true;
		}
		else
		{
			cout << "Ventana ya creada" << "\n";
			creado = true;
		}
		break;
	case 6:
		if (v6 == false)
		{
			v6 = true;
		}
		else
		{
			cout << "Ventana ya creada" << "\n";
			creado = true;
		}
		break;
	}
	return creado;
}

void acciones() {
	switch (accion)
	{
	case add:
		if (procesos != 6)
		{
			if (!verificarventana())
			{
				k->addprocess(ventana);
				cout << "El proceso fue agregado" << "\n";
				procesos++;
				cin.ignore();
			}

		}
		break;
	case remove:
		if (verificarexistencia() == true)
		{
			cout << "Ingrese el numero de ventana: ";
			cin >> ventana;
			procesos--;
			cin.ignore();

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

		break;
	case pause:
		cout << "\n" << "Ingrese el numero de ventana: ";
		cin >> ventana;
		break;
	case clear:
		cout << "\n" << "Ingrese el numero de ventana: ";
		cin >> ventana;
		break;
	case stats:
		cout << "\n" << "Ingrese el numero de ventana: ";
		cin >> ventana;
		break;
	}
}

int main()
{
	while (accion != 7)
	{
		tokens.empty();
		string dosomething;
		cout << "\n" << "Que desea hacer? " << "\n";
		cin >> dosomething;
		string buf; // Have a buffer string
		stringstream ss(dosomething); // Insert the string into a stream

		while (ss >> buf) {
			tokens.push_back(buf);
		}
		string acc = tokens[0];
		accion = tipo(acc);
		acciones();
	}
	cin.ignore();
}