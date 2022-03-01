#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 2

void cs(int i);
void rs();

int turno = 0;

void *tfunc(void *args)
{
	int i = *((int *)args);
	int j = 1 - i;

	int n;

	for (n = 0; n < 10; n++)
	{
		rs();
		while (turno != i)
			;
		cs(i);
		turno = j;
		rs();
	}
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];
	int pargs[NTHREADS] = {0, 1};

	for (i = 0; i < NTHREADS; i++)
		pthread_create(&tid[i], NULL, tfunc, &pargs[i]);

	for (i = 0; i < NTHREADS; i++)
		pthread_join(tid[i], NULL);
}

void cs(int i)
{
	printf("%d entra a la sección crítica\n", i);
	usleep(250000);
	printf("%d sale de la sección crítica\n", i);
}
void rs()
{
	usleep(250000);
}
