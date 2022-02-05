/*
1.- Desarrolla un programa donde un proceso
 padre crea un proceso hijo, al iniciar este
 proceso hijo, deberá matar o terminar a su padre.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	int p;
	p = fork();
	if (p == 0)
	{
		kill(getppid(), SIGKILL);
		exit(0);
	}
	printf("Soy el padre");
}