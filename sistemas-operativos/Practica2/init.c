#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NPROCS 6

volatile sig_atomic_t done = 0;

void proc(int n);

void term(int signum)
{
    printf("Caught!\n");
    done = 1;
}

void sighan(int s)
{
    printf("Señal recibida\n");
}

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
        /*
        struct sigaction action;
        memset(&action, 0, sizeof(action));
        action.sa_handler = term;
        sigaction(kill(0, SIGKILL), &action, NULL);
        */
        signal(SIGINT, sighan);
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