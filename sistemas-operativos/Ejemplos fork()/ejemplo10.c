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
	int status;
	
	p=fork();
	if(p==0)
		exit(0);	// El hijo termina
	
	wait(&status);	// La forma de evitar que permanezcan los zombies
					// es a través de la llamada wait, con wait, el padre
					// 1.- Si el hijo no ha terminado, lo espera
					// 2.- Si el hijo ya terminó, recoge su entrada
					//	de la tabla de procesos, evitan los procesos 
					// 	zombies.
	printf("Terminó el proceso hijo\n");
	sleep(10);
	printf("Termina el proceso\n");
	return(0);
}