/*
4.- Desarrolla un programa que solicite al 
usuario una cadena de caracteres, esa cadena 
será el nombre de un programa1 a ejecutarse, 
una vez que este programa termine de ejecutarse 
permitirá al usuario introducir otro programa a 
ejecutarse, esto terminará cuando el usuario introduzca exit. 
Para este ejercicio utiliza la llamada al sistema system(). 
En este ejercicio estamos haciendo nuestro primer shell o 
intérprete de comandos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char cmd[80];

    do
    {
        printf(">>>>$");
        scanf("%[^\n]%*c", cmd);
        system(cmd);
    } while (strcmp(cmd, "exit") != 0);
    return 0;
}