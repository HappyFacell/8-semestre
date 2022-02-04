#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login()
{
    printf("Login correcto");
    //Crear un proceso hijo que será reemplazado
    //por una sesión del shell (proceso sh).
}

int main()
{
    FILE *fptr;
    char c;

    int iterator;

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