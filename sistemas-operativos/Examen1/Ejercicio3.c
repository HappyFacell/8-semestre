#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int n;
    pid_t p;
    if (argc < 2)
    {
        n = 0;
    }
    else
    {
        n = atoi(argv[1]);
    }

    p = fork();
    for (int i = 0; i <= n; i++)
    {
        // p = fork();
        if (p == 0)
        {
            printf("%d\n", i);
            p = fork();
            if (p != 0)
            {
                exit(0);
            }
        }
        wait(NULL);
    }
    return 0;
}