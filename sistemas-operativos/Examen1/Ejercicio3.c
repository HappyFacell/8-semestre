#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int n = strtol(argv[1], NULL, 10);
    int i;
    int p;
    if (n > 0)
    {
        printf("%d\n", 0);
        p = fork();
        for (i = 1; i <= n; i++)
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
    }
    else
    {
        printf("%d\n", 0);
    }
    return 0;
}