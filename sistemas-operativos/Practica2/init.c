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
    /*
    Funcion para validar que se ejecuto el comando
    "shutdown".
    Lo que hace es leer el archivo signals.txt en donde
    si se ejecuta dicho comando se escibe un 15, con esto retornamos un 1
    salir del while de la linea 93.
    */
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
    /*
    Esta funcionn se ejecuta al inicio del programa, nos ayuda a escribir
    y/o sobre escribir en el archivo signals.txt.
    Esto nos ayuda a que cuando la funcion sighan se ejecuta sepa que todavia no se ejecuta
    el comando "shutdown".
    */
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
    /*
    Este ciclio while nos ayuda a siempre mantener las ventanas getty abiertas
    cuando se cierran o de ejecuta CTRL + C.
    */
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
    /*
    Borra las ventanas desplegadas por xterm,
    para esto ejecutamos el comando killall el cual mata a todos
    los procesos llamadas xterm.
    */
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