#include "stdafx.h"
#include <iostream>
#include <string>
#include <chrono>
#include "PCB.h"
#include "ClassB.h"
using namespace std;

typedef int(*CallBack)(int);
typedef int(Blink::*CallBackBlink)(int);

#pragma region define
#define MAX 6 //La cantidad maxima de procesos
#define RUNNING 1 //El proceso se esta ejecutando
#define BLOCKED 2 //El proceso se encuentra bloqueado
#define READY 3 //El proceso se encuentra listo para su ejecucion
#define SUSPENDED 4 //El proceso se ha suspendido
#define WAITING 5
#define DONE 6
#define READY_AND_SUSPENDED (READY | SUSPENDED) //Listo y suspendido
#define BLOCKED_AND_SUSPENDED ((BLOCKED | SUSPENDED) + 2) //Bloqueado y suspendido

#define SUCCESSFUL 0 //Resultado exitoso ->UTILIZADA EN TODAS LAS FUNCIONES<-

//DEFINICION DE CONSTANTES DEL RESULTADO DE AGREGAR UN PROCESO
#define UNAVAILABLE 1 //Posicion no disponible para agregar al proceso
#define OVERFLOW 2 //La cantidad de procesos agregados ha sido alcanzada
#define OUT_OF_RANGE 3 //El indice para agregar ha sido sobrepasado



//DEFINICION DE CONSTANTES DEL RESULTADO DE CORRER UN PROCESO
#define PROCESS_IS_NULL 1 //No hay proceso en esa posicion
#define PROCESS_IS_DONE 2 //El proceso ha sido terminado y desea ejecutarse
#define PROCESS_NOT_FOUND 3 //El proceso no ha sido encontrado
#pragma endregion


class Kernel
{
private:
	int id_count, quantum;

	int validatenewprocess(int index) {
		if (index >= MAX || index < 0)
			return OUT_OF_RANGE;
		if (this->pcb[index] != NULL)
		{
			if (this->pcb[index]->status != DONE)
				return UNAVAILABLE;
			else
				killProcessAt(index);
		}
		if (count >= MAX)
			return OVERFLOW;
		return SUCCESSFUL;
	}

	static void runProcess(PCB *pcb)
	{
		int result;
		int *function = pcb->function;
		pcb->status = RUNNING;
		if (pcb->obj != NULL)
		{
			CallBackBlink *cb = (CallBackBlink*)(function);
			result = (pcb->obj->**cb)(6);
		}
		else
		{
			CallBack cb = (CallBack)*(&function);
			result = cb(7);
		}
		pcb->status = DONE;
		cout << "Proceso terminado\nId de Proceso: " << pcb->getId() << "\nValor de Retorno: " << result << "\n\n";
	}

	static int validateProccess(PCB *current)
	{
		if (current == NULL)
			return PROCESS_IS_NULL;
		if (current->status == DONE)
			return PROCESS_IS_DONE;
		return SUCCESSFUL;
	}

	int firstAvailableIndex()
	{
		int i = 0;
		while (i < MAX)
		{
			if (this->pcb[i] == NULL)
				return i;
			else if (this->pcb[i]->status == DONE)
			{
				killProcessAt(i);
				return i;
			}
			i++;
		}
		return -1;
	}

	PCB *getProcessById(int id)
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL && pcb[i]->getId() == id)
				return pcb[i];
		return NULL;
	}

	int getProcessIndex(int id)
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL && pcb[i]->getId() == id)
				return i;
		return -1;
	}

public:
	int cambio = 0;
	PCB *pcb[MAX];
	int count;
	Kernel()
	{
		this->count = this->id_count = 0;
		for (int i = 0; i < MAX; i++)
			this->pcb[i] = NULL;
	}
	~Kernel()
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL)
			{
				killProcessAt(i);
				pcb[i] = NULL;
			}
		this->count = 0;
	}
	//------------------------------------------------------------------------------------------------------------
	int addprocess(int id) {
		int result = validatenewprocess(count);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id, READY);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}

	int addProcess(int *callback, int id)
	{
		int index = getProcessIndex(id);
		int result = validatenewprocess(index);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id, READY, callback);
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}

	int changequantum(int id, int q) {
		int index = getProcessIndex(id);
		this->pcb[index]->quantum = q;
		cambio = 1;
		return SUCCESSFUL;
	}

	int agregarclics(int id, int clic) {
		int index = getProcessIndex(id);
		int c = this->pcb[index]->clics;
		c = c + clic;
		this->pcb[index]->clics = c;
		return SUCCESSFUL;
	}

	int killProcessAt(int index)
	{
		if (index >= MAX || index < 0)
			return OUT_OF_RANGE;
		if (this->pcb[index] == NULL)
			return PROCESS_IS_NULL;
		count--;
		this->pcb[index]->~PCB();
		this->pcb[index] = NULL;
		return SUCCESSFUL;
	}

	int killProcessById(int id)
	{
		int index = getProcessIndex(id);
		if (index < 0)
			return PROCESS_NOT_FOUND;
		killProcessAt(index);
		return SUCCESSFUL;
	}

	int runAllProcesses()
	{
		for (int i = 0; i < MAX; i++)
		{
			if (cambio != 1) //todos tienen el mismo quantum
			{
				runProcessAt(i);
				killProcessAt(i);
				int index = getProcessIndex(1);
				int tempo = this->pcb[index]->quantum;
				//_sleep(tempo);
			}
			else
			{
				runbyquantum();
			}

		}
		return SUCCESSFUL;
	}

	int runProcessAt(int id) {
		int index = getProcessIndex(id);
		runProcessAti(index);
	}

	int runProcessAti(int index)
	{
		PCB *current = this->pcb[index];
		int result = validateProccess(current);
		if (result != SUCCESSFUL)
			return result;
		runProcess(current);
		return SUCCESSFUL;
	}

	int runbyquantum() {
		for (size_t i = 0; i < MAX; i++)
		{
			int index = getProcessIndex(i);
			int tempo = this->pcb[index]->quantum;
			PCB *current = this->pcb[index];
			int result = validateProccess(current);
			if (result != SUCCESSFUL)
				return result;
			runProcess(current);
			//_sleep(tempo);
		}
		return SUCCESSFUL;
	}

	int getstatus(int i) {
		int p = this->pcb[i]->getStatus();
		return p;
	}
	//-------------------------------------------------------------------------------------------------------------

	/*int addProcess(int *callback)
	{
		int result = validatenewprocess(count);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback, quantum);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}



	int addProcess(int *callback, ClassB *obj)
	{
		int result = validatenewprocess(count);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback, obj);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}

	int addProcess(int *callback, ClassB *obj, int index)
	{
		int result = validatenewprocess(index);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback, obj);
		this->pcb[index] = pcb;
		index++;
		return SUCCESSFUL;


	/*

	int runProcessById(int id)
	{
		PCB *current = getProcessById(id);
		int result = validateProccess(current);
		if (result != SUCCESSFUL)
			return result;
		runProcess(current);
		return SUCCESSFUL;
	}


*/

};

