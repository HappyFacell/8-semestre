#include <scheduler.h>
#include <stdlib.h>

extern THANDLER threads[MAXTHREAD];
extern int currthread;
extern int blockevent;
extern int unblockevent;

QUEUE ready[MAXTHREAD]; // cola de queues
QUEUE waitinginevent[MAXTHREAD];

int count = 0; // Num hilos

void scheduler(int arguments)
{
	int old, next;
	int changethread = 0;
	int waitingthread = 0;

	int event = arguments & 0xFF00;
	int callingthread = arguments & 0xFF;

	int priority = 0;

	if (event == NEWTHREAD)
	{
		// Un nuevo hilo va a la cola de listos
		threads[callingthread].status = READY;
		_enqueue(&ready[0], callingthread);
		count++;
	}

	if (event == BLOCKTHREAD)
	{

		threads[callingthread].status = BLOCKED;
		_enqueue(&waitinginevent[blockevent], callingthread);

		changethread = 1;
	}

	if (event == ENDTHREAD)
	{
		threads[callingthread].status = END;
		changethread = 1;
		count--; // Quitar hilo terminado
	}

	if (event == UNBLOCKTHREAD)
	{
		threads[callingthread].status = READY;
		_enqueue(&ready[priority], callingthread);
	}

	if (event == TIMER)
	{

		if (count != 0)
		{
			if (priority + 1 < MAXTHREAD)
			{
				priority++; // incrementa prioridad
			}
		}

		threads[callingthread].status = READY;
		_enqueue(&ready[priority], callingthread);
		changethread = 1;
	}

	if (changethread)
	{
		old = currthread;
		for (int i = 0; i < MAXTHREAD; i++)
		{ // Por cada cola
			if (!(_emptyq(&ready[i])))
			{
				priority = i; // index de la queue en la queue
				break;
			}
		}

		next = _dequeue(&ready[priority]); // Next thread

		threads[next].status = RUNNING;
		_swapthreads(old, next);
	}
}
