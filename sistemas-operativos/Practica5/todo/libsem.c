#include <pthread_utils.h>
#include <libsem.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Macro que incluye el código de la instrucción máquina xchg
#define atomic_xchg(A, B) __asm__ __volatile__( \
	"   lock xchg %1,%0 ;\n"                    \
	: "=ir"(A)                                  \
	: "m"(B), "ir"(A));

int g = 0;

void initsem(SEMAPHORE *s, int val)
{
	int l;
	int g = 0;
	l = 1;

	do
	{
		atomic_xchg(l, g);
	} while (l != 0);
	initqueue(&s->queue);
	s->count = val;

	g = 0;
	l = 1;

	sleep(rand() % 3);
}

void waitsem(SEMAPHORE *s)
{
	int l;

	int g = 0;

	l = 1;
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

	g = 0;
	l = 1;

	sleep(rand() % 3);
}

void signalsem(SEMAPHORE *s)
{
	int l;
	int g = 0;

	l = 1;
	do
	{
		atomic_xchg(l, g);
	} while (l != 0);
	s->count++;
	pthread_t tid;

	if (s->count <= 0)
	{
		tid = dequeue(&s->queue);
		unblock_thread(tid);
	}

	g = 0;
	l = 1;

	sleep(rand() % 3);
}
