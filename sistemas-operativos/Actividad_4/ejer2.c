/*
2.- Desarrolla un programa donde un proceso
 padre crea un hijo, el padre tendrá una duración
 de 20 segundos y el hijo una duración de 1 segundo.
 Antes de que el padre termine observa qué procesos hay,
¿En qué estado se encuentra el hijo?
En un proceso zombie
, 
¿por qué?
Porque el padre no espera a que el hijo termine, y se queda como un proceso zombie hasta que el programa termine
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int p;

    p = fork();
    if (p == 0)
    {
        printf("soy el hijo: %d\n", getpid());
        sleep(1);
        system("ps");
        kill(getpid(), SIGUSR1);
        exit(0);
    }
    else
    {

        printf("Soy el padre: %d\n", getpid());
        sleep(20);
        system("ps");
    }

    printf("Fin\n");
    return 0;
}