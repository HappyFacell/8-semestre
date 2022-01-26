#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Hola mundo, mi pid es %d\n",getpid());
	fork();
	printf("Adios mundo desde el proceso pid=%d\n",getpid());
	return(0);
}