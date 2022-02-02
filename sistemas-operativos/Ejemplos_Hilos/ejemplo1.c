#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *holamundo(void *args)
{
	sleep(2);
	printf("Hola mundo\n");
}

int main()
{
	pthread_t tid;
	
	pthread_create(&tid,NULL,holamundo,NULL);
	
	pthread_join(tid,NULL);

	return 0;
}