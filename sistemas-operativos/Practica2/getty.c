#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
int main()
{
<<<<<<< HEAD
    FILE *fptr;
    char c;
    char u[20];
    char p[20];
    if ((fptr = fopen("passwd.txt", "r")) == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
  
    c = fgetc(fptr);
    while (c != EOF)
    {
        int x=0;
        while(c != ':'){
            u[0] = c;
            x++;
        }
        x=0;
        while (c != '\n'){
            p[x] = c;
            x++
        }
        printf (",%c", c);
        c = fgetc(fptr);
    }
  
    fclose(fptr);
/*
    printf("%lu %lu:", strlen(id), strlen(studentID));


    do{
        printf("\nLogin:");
=======
    static const char studentID[] = "Clarance", password[] = "123456";
    char id[8], p[6];
    int n = 1, x, y;

    printf("%lu %lu:", strlen(id), strlen(studentID));

    do
    {
        printf("\nStudent_ID:");
>>>>>>> 8292af94d9e5870fe32d8e1ec716aea7cd9d862d
        scanf("%s", id);
        fflush(stdout);

        printf("\nPassword:");
        scanf("%s", p);
        fflush(stdout);

        x = strcmp(id, studentID);
        y = strcmp(p, password);

        if (x == 0 && y == 0)
        {
            printf("\nSucessfully Logged In");
        }
        else
        {
            printf("\nWrong Password, try again  %d", 5 - n);
            getchar();
            n++;
        }

        if (n > 5)
        {
            printf("\nAccess Denied");
            getchar();
        }

<<<<<<< HEAD
    }while (n<=5);
    */
=======
    } while (n <= 5);
>>>>>>> 8292af94d9e5870fe32d8e1ec716aea7cd9d862d
}