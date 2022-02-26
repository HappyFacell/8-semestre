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
        n = 0;
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
    printf("%d\n", n);
    exit(0);
}