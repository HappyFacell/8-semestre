/*
5.- Repite el ejercicio anterior, pero ahora no podrás usar 
la llamada al sistema system(), por lo que será necesario 
que crees un nuevo proceso (hijo) el cuál ejecutará el programa 
que indicaste; Una vez que termine el programa de ejecutarse permitirá 
al usuario introducir otro programa a ejecutarse, esto terminará cuando 
el usuario introduzca exit.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

enum
{
    MAXLINE = 256
};

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf(">>>>>$");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {

        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            execlp(buf, buf, (char *)NULL);
            exit(127);
        }

        if (waitpid(pid, &status, 0) < 0)
            perror("waitpid");

        if (strcmp(buf, "exit") == 0)
        {
            break;
        }

        printf(">>>>>$");
    }

    return 0;
}
