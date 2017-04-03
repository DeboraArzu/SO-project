#pragma once
#include "Blink.h"

class PCB
{
private:
	int id;
	
public:
	int status, *function, quantum, clics;
	Blink *obj;

	PCB(int id, int status)
	{
		this->id = id;
		this->status = status;
		this->quantum = 2000;
		this->clics = 0;
	}

	PCB(int id, int status, int *callback)
	{
		this->id = id;
		this->status = status;
		this->quantum = 2000; //milisegundos
		this->clics = 0;
		this->function = callback;
	}

	/*
	PCB(int id, int status, int *callback, ClassB *obj)
	{
		this->id = id;
		this->quantum = 1000;
		this->status = status;
		this->function = callback;
		this->obj = obj;
	}*/
	~PCB()
	{
		this->id = this->status = 0;
		this->quantum = 0;
		this->function = NULL;
		if (this->obj != NULL)
		{ 
			this->obj = NULL;
		}
	}

	int getId()
	{
		return this->id;
	}
	int getStatus()
	{
		return this->status;
	}
};

