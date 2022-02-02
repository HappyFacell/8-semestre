#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4

void *holamundo(void *args)
{
	printf("Hola mundo\n");
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];
	
	for(i=0;i<NTHREADS;i++)
		pthread_create(&tid[i],NULL,holamundo,NULL);
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);

	return 0;
}