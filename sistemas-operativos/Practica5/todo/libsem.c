#include <pthread_utils.h>
#include <libsem.h>
#include <unistd.h>
#include <stdlib.h>

/*
	La estructura del semáforo:
	typedef struct {
		int count;
		QUEUE queue;
	} SEMAPHORE;

	Para acceder a sus elementos:
	&SEMAPHORE->elemento
*/

// Macro que incluye el código de la instrucción máquina xchg que hace un intercambio atómico de dos variables.
#define atomic_xchg(A, B) __asm__ __volatile__( \
	"   lock xchg %1,%0 ;\n"                    \
	: "=ir"(A)                                  \
	: "m"(B), "ir"(A));

int g;
int l = 1;

/*
	Hay que inicializar la cola del semáforo s aquí utilizando la función de include/queues.h
	llamada initqueue(QUEUE *q)
*/

void initsem(SEMAPHORE *s, int val)
{
	g = 0;
	initqueue(&s->queue);
	s->count = val;
}

/*	Wait(s):
		s.contador--;
		if s.contador < 0 then
		{
			poner este proceso en s.queue;
			bloquear este proceso
		}
*/
void waitsem(SEMAPHORE *s)
{

	do
	{
		atomic_xchg(l, g);
	} while (l != 0);
	s->count--;
	pthread_t tid = pthread_self();

	if (s->count < 0)
	{
		enqueue(&s->queue, tid);
		block_thread();
	}
}

/*	Signal(s):
		s.contador++;
		if s.contador <= 0
		{
			quitar un proceso P de s.queue;
			poner el proceso p en la cola de listos
		}
*/
void signalsem(SEMAPHORE *s)
{
	s->count++;
	pthread_t tid;

	if (s->count <= 0)
	{
		tid = dequeue(&s->queue);
		unblock_thread(tid);
	}

	g = 0;
	l = 1;
}
