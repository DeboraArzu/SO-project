#include "stdafx.h"
#include "Kernel.h"
#include "Blink.h";
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
int qua = 2000;
std::vector<string> tokens; // Create vector to hold our words

bool v1, v2, v3, v4, v5, v6 = false;

Kernel *k = new Kernel();
Blink *clase = new Blink();

#pragma region variables
#define add 1
#define remove 2
#define quantum 3
#define pause 4
#define dclear 5
#define stats 6
#define salir 7
#pragma endregion

int tipo(string tipo) {
	//	int a = strcmp((char*)tipo.c_str(), "salir");
	if (strcmp((char*)tipo.c_str(), "add") == 0)
	{
		istringstream(tokens[1]) >> ventana;
		return add;
	}
	else if (strcmp((char*)tipo.c_str(), "remove") == 0)
	{
		istringstream(tokens[1]) >> ventana;
		return remove;
	}
	else if (strcmp((char*)tipo.c_str(), "pause") == 0)
	{
		istringstream(tokens[1]) >> ventana;
		return pause;
	}
	else if (strcmp((char*)tipo.c_str(), "quantum") == 0)
	{
		istringstream(tokens[1]) >> ventana;
		istringstream(tokens[2]) >> qua;
		return quantum;
	}
	else if (strcmp((char*)tipo.c_str(), "clear") == 0)
	{
		//clear screen and remove al process
		return dclear;
	}
	else if (strcmp((char*)tipo.c_str(), "stats") == 0)
	{
		istringstream(tokens[1]) >> ventana;
		return stats;
	}
	else if (strcmp((char*)tipo.c_str(), "salir") == 0)
	{
		exit(0);
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

static int function1(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 1 << "\n";
	return 1;
}

void acciones() {
	switch (accion)
	{
	case add:
		if (procesos != 6)
		{
			if (!verificarventana())
			{
				k->addProcess(ventana);
				cout << "El proceso fue agregado" << "\n";
				procesos++;
				cin.ignore();
			}
		}
		break;
	case remove:
		if (verificarexistencia() == true)
		{
			k->killProcessById(ventana);
			procesos--;
			cin.ignore();

		}
		break;
	case quantum:

		k->changequantum(ventana, qua);
		cin.ignore();
		cout << "El quantum de los procesos de la ventana " << ventana << "han sido cambiados";
		break;
	case pause:
		//pause
		break;
	case dclear:
		for (int i = 0; i < MAX; i++)
		{
			k->killProcessById(i);
		}
		cout << "procesos eliminados";
		break;
	case stats:
		//stats
		cout << "Estado del proceso";
		cout << k->getstatus(ventana);
		cout << "Tiempo que lleva corriendo";
		break;
	case salir:
		exit(0);
		break;
	}
}

void limpiartokens() {
	tokens.clear();
}


int main()

{
	while (accion != 7)
	{
		tokens.clear();
		string dosomething = "so";
		cout << "\n" << "Que desea hacer? " << "\n";
		cin.getline((char*)dosomething.c_str(), 256);
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