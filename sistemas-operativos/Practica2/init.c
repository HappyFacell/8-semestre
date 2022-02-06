#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

#define NPROCS 6

volatile sig_atomic_t done = 0;

int sighan()
{
    const char *filename = "signals.txt";

    FILE *input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);

    struct stat sb;
    if (stat(filename, &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *validador = malloc(sb.st_size);
    fread(validador, sb.st_size, 1, input_file);

    fclose(input_file);

    if (validador[0] == '1' && validador[1] == '5')
    {
        return 1;
    }
    free(validador);
    return 0;
}

void init()
{
    char str[5];
    sprintf(str, "%d", 0);
    const char *filename = "signals.txt";

    FILE *output_file = fopen(filename, "w+");
    if (!output_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(str, 1, strlen(str), output_file);

    fclose(output_file);
}
int main()
{
    init();
    int flag = 0;
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

        int temp = wait(&status);
        if (temp > 0)
        {

            if (sighan())
            {
                break;
            }
            p = fork();
            if (p == 0)
            {
                execlp("xterm", "xterm", "-e", "./getty", NULL);
                exit(1);
            }
        }
    }

    // system("killall xterm");
    p = fork();
    if (p == 0)
    {
        execlp("killall", "killall", "xterm", NULL);
        exit(10);
    }

    wait(&status);

    printf("Fin!! :D\n");

    return 0;
}