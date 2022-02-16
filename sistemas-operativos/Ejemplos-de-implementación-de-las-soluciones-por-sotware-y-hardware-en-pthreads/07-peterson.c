#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 2

#define TRUE 1
#define FALSE 0

void cs(int i);
void rs();
void x();

int flag[NTHREADS] = {FALSE, FALSE};
int turno = 0;

void *tfunc(void *args)
{
	int i = *((int *)args);
	int j = 1 - i;

	int n;

	for (n = 0; n < 10; n++)
	{
		rs();
		// Sección de entrada
		flag[i] = TRUE;
		x(); // Pongo mi bandera indicando que quiero entrar
		turno = j;
		x(); // Soy educado, y cedo el turno al otro si también quiere entrar
		while (flag[j] && turno != i)
			; // Espera

		cs(i);

		// Sección de salida
		flag[i] = FALSE;
		turno = j;

		rs();
	}
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];
	int pargs[NTHREADS] = {0, 1};
	srand(getpid());

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
	sleep(rand() % 3);
}

void x()
{
	usleep(250000);
}