#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    static const char studentID[] = "Clarance", password[] = "123456";
    char id[8], p[6];
    int n = 1, x, y;

    printf("%lu %lu:", strlen(id), strlen(studentID));

    do
    {
        printf("\nStudent_ID:");
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

    } while (n <= 5);
}