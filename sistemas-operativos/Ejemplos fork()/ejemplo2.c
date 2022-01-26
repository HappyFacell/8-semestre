#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p;
	
	printf("Hola mundo, soy el proceso %d\n",getpid());
	
	p=fork();
	
	if(p!=0)  // Esta condición se va a cumplir en el padre
		printf("Yo soy el padre, mi pid es %d\n",getpid());
	else	// else lo va a hacer el hijo
		printf("Yo soy el hijo, mi pid es %d\n",getpid());
	
	return 0;	
}