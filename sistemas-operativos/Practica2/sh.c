#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

enum
{
    MAXLINE = 256
};

void sigint_handler()
    {
        printf("killing process %d\n",getppid());
        kill(getppid(), SIGINT);
    }

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("sh  >");
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
            exit(127);
            break;
        }
        if(strcmp(buf, "Shutdown") == 0){
            sigint_handler();
        }

        printf("sh  >");

    }

    return 0;
}
