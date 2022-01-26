#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Hola, soy el proceso %d\n",getpid());
	// system("./holamundo"); // Llamada prohibida en la práctica 2
	execlp("./holamundo","holamundo",NULL);
	printf("Adios, soy el proceso %d\n",getpid());
	return 0;
}