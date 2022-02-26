#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t p;
    printf("fork creation\n");
    p = fork();
    for (int i = 0; i < 3; i++)
    {
        if (p != 0)
        {
            printf("fork creation\n");
            p = fork();
        }
    }
    if (p != 0)
    {
        printf("Dormi 10 seg\n");
        sleep(10);
    }
    else if (p == 0)
    {
        printf("Dormi 5 seg\n");
        sleep(5);
    }

    return 0;
}