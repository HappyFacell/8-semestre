/*
3.- Desarrolla un programa donde un proceso padre crea un hijo,
 el padre tendrá una duración de 1 segundo y el hijo una duración 
 de 20 segundos. Antes de que el hijo termine observa qué procesos hay, 
 ¿En qué estado se encuentra el padre?
 No se encuentra el padre ya que lo terminamos.
 , 
 ¿por qué?
 No se encuentra porque ahora el proceso hijo tomo el rol del padre.
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
        sleep(20);
        system("ps");
        printf("Adios papa\n");
        exit(0);
    }
    else
    {
        printf("Soy el padre: %d\n", getpid());
        sleep(1);
        system("ps");
        printf("Adios mundo cruel ＞﹏＜\n");
        exit(0);
    }
}