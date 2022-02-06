#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

enum
{
    MAXLINE = 256
};

void sigint_handler(int sig)
{
    char str[5];
    sprintf(str, "%d", sig);
    const char *filename = "signals.txt";

    FILE *output_file = fopen(filename, "w+");
    if (!output_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(str, 1, strlen(str), output_file);
    fclose(output_file);
    kill(getppid(), sig);
}

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    int flag = 0;

    printf("sh  >");

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {

        signal(SIGTERM, sigint_handler);
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if (buf[strlen(buf) - 1] == 38)
        {
            buf[strlen(buf) - 1] = 0;
            buf[strlen(buf) - 1] = 0;
            flag = 1;
        }

        if ((pid = fork()) < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            execlp(buf, buf, (char *)NULL);
            exit(127);
        }
        if (!flag)
        {

            if (waitpid(pid, &status, 0) < 0)
            {

                perror("waitpid");
            }
        }
        if (strcmp(buf, "exit") == 0)
        {
            exit(127);
            break;
        }
        if (strcmp(buf, "shutdown") == 0)
        {
            kill(getpid(), SIGTERM);
            break;
        }
        flag = 0;
        printf("sh  >");
    }

    return 0;
}
