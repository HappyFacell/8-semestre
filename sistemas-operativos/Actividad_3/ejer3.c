/*
3.- Desarrolla un programa que reciba como argumento 
desde la línea de comandos un valor de entrada n cuyo 
significado sera un número de procesos a crear, de manera 
que cuando ejecutes tu programa este será el proceso padre que 
creará solamente n procesos hijos a un nivel, cada proceso hijo 
mostrará su número que será de 1 hasta n.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void proc(int n);

int main(int argc, char *argv[])
{
    int i;
    pid_t p;
    int status;
    int n;

    if (argc < 2)
    {
        n = 1;
    }
    else
    {
        n = atoi(argv[1]);
    }

    for (i = 0; i <= n; i++)
    {
        p = fork();
        if (p == 0)
            proc(i);
    }

    for (i = 0; i <= n; i++)
        wait(&status);
    
    printf("Fin\n");
}

void proc(int n)
{
    printf("Soy el proceso hijo %d, mi pid es %d\n", n, getpid());
    exit(0);
}