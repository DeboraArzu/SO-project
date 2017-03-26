#pragma once
#include "ClassB.h"

class PCB
{
private:
	int id;
	
public:
	int status, *function, quantum;
	ClassB *obj;

	PCB(int id, int status)
	{
		this->id = id;
		this->status = status;
		this->quantum = 1000;
	}

	PCB(int id, int status, int *callback, int quantum)
	{
		this->id = id;
		this->status = status;
		this->function = callback;
		this->quantum = 1000;
		this->obj = NULL;
	}
	PCB(int id, int status, int *callback, ClassB *obj)
	{
		this->id = id;
		this->quantum = 1000;
		this->status = status;
		this->function = callback;
		this->obj = obj;
	}
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
};

