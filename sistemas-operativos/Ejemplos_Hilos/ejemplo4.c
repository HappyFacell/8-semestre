#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4

void *holamundo(void *args)
{
	int nthread = *((int *) args);
	printf("Hola mundo desde el hilo %d\n",nthread);
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];
	int parArr[NTHREADS];
	
	for(i=0;i<NTHREADS;i++)
	{
		parArr[i]=i;		
		pthread_create(&tid[i],NULL,holamundo,(void *) &parArr[i]);
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);

	return 0;
}