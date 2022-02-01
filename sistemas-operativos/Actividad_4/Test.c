#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighan(int s)
{
	printf("Señal recibida\n");
}

int main()
{
	signal(SIGINT,sighan);
	while(1)
	{
		printf("Hola mundo\n");
		sleep(3);
	}
}
		
