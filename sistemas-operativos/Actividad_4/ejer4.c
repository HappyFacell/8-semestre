/*
4.- Desarrolla un programa que al ejecutarse 
cree dos procesos hijos y cada uno de los hijos
creará 3 nuevos procesos hijos. 
De esta manera habrá un proceso padre, 
dos procesos hijos y seis procesos nieto. 
Los hijos y los nietos deberán tener al final la 
instrucción sleep(20), pero el padre después de 
ejecutar la instrucción sleep(5) deberá terminar 
a todos los hijos y nietos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int h[7];
    int r[7];
    h[0] = fork();
    if (h[0] == 0)
    {
        h[2] = fork();
        if (h[2] == 0)
        {
            sleep(20);
        }
        else
        {
            r[2] = h[2];
        }
        h[3] = fork();
        if (h[3] == 0)
        {
            sleep(20);
        }
        else
        {
            r[3] = h[3];
        }
        h[4] = fork();
        if (h[4] == 0)
        {
            sleep(20);
        }
        else
        {
            r[4] = h[4];
        }
        sleep(20);
        exit(0);
    }
    else
    {
        r[0] = h[0];
        h[1] = fork();
        if (h[1] == 0)
        {
            h[5] = fork();
            if (h[5] == 0)
            {
                sleep(20);
            }
            else
            {
                r[5] = h[5];
            }
            h[6] = fork();
            if (h[6] == 0)
            {
                sleep(20);
            }
            else
            {
                r[6] = h[6];
            }
            h[7] = fork();
            if (h[7] == 0)
            {
                sleep(20);
            }
            else
            {
                r[7] = h[7];
            }
            sleep(20);
        }
        else
        {
            r[1] = h[1];
        }
        sleep(5);
        printf("Adiós vástagos\n");
        for (int x = 0; x <= 7; x++)
        {
            printf("1");
            kill(r[x], SIGKILL);
        }
        exit(0);
    }
}