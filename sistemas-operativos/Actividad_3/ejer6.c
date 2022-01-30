/*
6.- Repite el ejercicio anterior, 
pero ahora una vez introducido el 
nombre del programa, no deberá esperar 
a que este termine, si no deberá permitir 
que se introduzca el nombre de otro programa 
que también se lanzará a ejecución, es decir, 
los programas se ejecutarán en segundo plano.
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

        if (strcmp(buf, "exit") == 0)
        {
            break;
        }

        printf(">>>>>$");
    }

    return 0;
}
