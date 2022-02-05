#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NPROCS 6

void proc(int n);

int main()
{
    int i;
    pid_t p;
    int status;

    for (i = 1; i <= NPROCS; i++)
    {
        p = fork();
        if (p == 0)
        {
            execlp("xterm", "xterm", "-e", "./getty", NULL);
            exit(1);
        }
    }

    while (1)
    {
        int temp = wait(&status);
        if (temp > 0)
        {
            p = fork();
            if (p == 0)
            {
                execlp("xterm", "xterm", "-e", "./getty", NULL);
                exit(1);
            }
        }
    }
}