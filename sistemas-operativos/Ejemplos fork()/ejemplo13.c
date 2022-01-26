#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t p;
	int status;
	printf("Hola, soy el proceso %d\n",getpid());
	// system("./holamundo"); // Llamada prohibida en la práctica 2
	p=fork();
	if(p==0)
		execlp("./holamundo","holamundo",NULL);
	wait(&status);
	printf("Adios, soy el proceso %d\n",getpid());
	return 0;
}