/*
4.- Desarrolla un programa que al ejecutarse 
cree dos procesos hijos y cada uno de los hijos
creará 3 nuevos procesos hijos. 
De esta manera habrá un proceso padre, 
dos procesos hijos y seis procesos nieto. 
Los hijos y los nietos deberán tener al final la 
instrucción sleep(20), pero el padre después de 
ejecutar la instrucción sleep(5) deberá terminar 
a todos los hijos y nietos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>

void matarTodo(){
	printf("Matando a todos los procesos\n");
	system("killall ejer4");
}


int main(){
	signal(SIGUSR1,matarTodo);
	printf("Soy el main, mi pid es %d\n",getpid());
		for(int i=0;i<2;i++){
			int h=fork();
			if(h==0){
				printf("Soy %d, hijo de %d\n",getpid(),getppid());
				for(int j=0;j<3;j++){
					int n=fork();
					if(n==0){
						printf("Soy %d, hijo de %d\n",getpid(),getppid());
						sleep(20);
						exit(1);
					}
				}
				sleep(20);
				exit(0);
				}
			}
	
	
	sleep(4);
	kill(getpid(),SIGUSR1);
}