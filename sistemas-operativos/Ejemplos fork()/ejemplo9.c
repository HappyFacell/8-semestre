/* Ejemplo de procesos zombie */
/* Un proceso zombie se da cuando un proceso crea un hijo, el hijo termina
   y el padre sigue ejecutándose */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t p;
	
	p=fork();
	if(p==0)
		exit(0);	// El hijo termina
	
	sleep(20);
	printf("Termina el proceso\n");
	return(0);
}