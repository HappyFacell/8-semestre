#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 1000
#define NTHREADS 2

int g = 0;

void *tfunc(void *args)
{
	int i;
	for (i = 0; i < MAX; i++)
		g++;
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];

	for (i = 0; i < NTHREADS; i++)
		pthread_create(&tid[i], NULL, tfunc, NULL);

	for (i = 0; i < NTHREADS; i++)
		pthread_join(tid[i], NULL);

	printf("g = %d\n", g);
}