/*
1.- Desarrolla un programa donde un proceso
 padre crea un proceso hijo, al iniciar este
 proceso hijo, deberá matar o terminar a su padre.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int flag = 0;

void sighan(int s)
{
	printf("Señal recibida, es la hora\n");
	flag = 1;
}

void timerproc()
{
	sleep(10);
	kill(getppid(), SIGUSR1);
	printf("Senal del padre matada\n");
	exit(0);
}

int main()
{
	int p;
	signal(SIGUSR1, sighan);

	p = fork();
	if (p == 0)
	{
		timerproc();
	}

	while (!flag)
	{
		printf("Hola mundo\n");
		sleep(3);
	}

	printf("Fin\n");
}