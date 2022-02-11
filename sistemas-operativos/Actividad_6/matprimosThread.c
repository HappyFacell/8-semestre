#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define NTHREADS 4

#define SIZE 4000

#define INICIAL 900000000
#define FINAL 1000000000

int mat[SIZE][SIZE];

void initmat(int mat[][SIZE]);
void printnonzeroes(int mat[SIZE][SIZE]);
int isprime(int n);
void *primesearch(void *args);

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

	// Inicializa la matriz con números al azar
	initmat(mat);

	pthread_t tid[NTHREADS];
	int args[NTHREADS];

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	// Eliminar de la matriz todos los números que no son primos
	// Esta es la parte que hay que paralelizar

	int i;
	for (i = 0; i < NTHREADS; i++)
	{

		args[i] = i;
		pthread_create(&tid[i], NULL, primesearch, &args[i]);
	}

	for (i = 0; i < NTHREADS; i++)
		pthread_join(tid[i], NULL);

	// Hasta aquí termina lo que se tiene que hacer en paralelo
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;

	printnonzeroes(mat);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}

void *primesearch(void *args)
{

	int nthread = *((int *)args);
	int i, j;
	for (i = nthread; i < SIZE; i += NTHREADS)
		for (j = 0; j < SIZE; j++)
			if (!isprime(mat[i][j]))
				mat[i][j] = 0;

	return NULL;
}

void initmat(int mat[][SIZE])
{
	int i, j;

	srand(getpid());

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			mat[i][j] = INICIAL + rand() % (FINAL - INICIAL);
}

void printnonzeroes(int mat[SIZE][SIZE])
{
	int i, j;

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (mat[i][j] != 0)
				printf("%d\n", mat[i][j]);
}

int isprime(int n)
{
	int d = 3;
	int prime = 0;
	int limit = sqrt(n);

	if (n < 2)
		prime = 0;
	else if (n == 2)
		prime = 1;
	else if (n % 2 == 0)
		prime = 0;
	else
	{
		while (d <= limit && n % d)
			d += 2;
		prime = d > limit;
	}
	return (prime);
}