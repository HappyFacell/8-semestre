#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void login()
{
    int p = fork();
    if (p == 0)
    {
        execlp("./sh", "./sh", NULL);
        exit(0);
    }
    else
    {
        wait(0);
    }
}
void sighan(int s)
{
    kill(getppid(), SIGTERM);
    printf("%d\n", s);
}

int main()
{
    signal(SIGTERM, sighan);
    FILE *fptr;
    char c;

    int iterator;
    printf("%d\n", getppid());
    do
    {
        char u[20];
        char p[20];
        char cu[20];
        char cp[20];
        printf("\nLogin:");
        scanf("%s", u);
        fflush(stdout);

        printf("\nPassword:");
        scanf("%s", p);
        fflush(stdout);

        if ((fptr = fopen("passwd.txt", "r")) == NULL)
        {
            printf("Cannot open file \n");
            exit(0);
        }

        c = fgetc(fptr);
        while (c != EOF)
        {
            iterator = 0;
            while (c != 58)
            {
                if (c == EOF)
                {
                    break;
                }
                if (c != '\n')
                {
                    cu[iterator] = c;
                    iterator++;
                    c = fgetc(fptr);
                }
            }
            cu[iterator] = '\0';

            if (c == EOF)
            {
                break;
            }
            c = fgetc(fptr);
            iterator = 0;

            while (c != '\n')
            {
                if (c == EOF)
                {
                    break;
                }
                cp[iterator] = c;
                iterator++;
                c = fgetc(fptr);
            }
            cp[iterator] = '\0';
            c = fgetc(fptr);
            if (strcmp(u, cu) == 0 && strcmp(p, cp) == 0)
            {
                login();
            }
        }
    } while (1);

    fclose(fptr);
}