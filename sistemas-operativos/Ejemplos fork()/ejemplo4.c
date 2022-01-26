#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t p;
	
	p=fork();
	
	if(p==0) // Hijo
	{
		sleep(7); 	// Espera 5 segundos
		printf("Hola, soy el hijo");
	}
	else
	{
		printf("Yo soy el padre\n");
		sleep(2);
	}
}