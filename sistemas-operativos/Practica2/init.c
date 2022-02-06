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

void proc(int n);

void term(int signum)
{
    printf("Caught!\n");
    done = 1;
}

void sighan()
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
            kill(getppid(), SIGTERM);
            execlp("killall xterm", "killall xterm", NULL);
            exit(0);
    }
    else
    {
        printf("Señal recibida\n");
        printf("No es 15\n");
    }
    free(validador);
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
    printf("Done Writing!\n");

    fclose(output_file);
}
int main()
{
    init();
    int i;
    pid_t p;
    int status;

    for (i = 1; i <= NPROCS; i++)
    {
        p = fork();
        if (p == 0)
        {
            printf("%d\n", getppid());
            execlp("xterm", "xterm", "-e", "./getty", NULL);
            exit(1);
        }
    }
    while (1)
    {

        int temp = wait(&status);
        if (temp > 0)
        {

            p = fork();
            if (p == 0)
            {
                sighan();
                execlp("xterm", "xterm", "-e", "./getty", NULL);
                exit(1);
            }
        }
    }
}