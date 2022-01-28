#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t p;
    int i;
    int inicio = 10;
    int max = inicio + 10;
    int min = inicio - 10;
    int status;

    p = fork();

    if (p == 0) // En el hijo
    {
        for (i = 1; i <= 5; i++)
        {
            printf("Hijo i=%d\n", i);
            sleep(1);
        }
        exit(2);
    }
    else // En el padre
    {
        wait(&status);
        printf("Hijo termina con status %d\n", status >> 8);
        for (i = 0; i <= 5; i++)
        {
            printf("Padre i=%d\n", i);
            sleep(1);
        }
    }
    return 0;
}