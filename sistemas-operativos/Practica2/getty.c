#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void login()
{
    int p = fork();
    if (p == 0)
    {
        execlp("./sh", "./sh", NULL);
        exit(0);
    }
    else
    {
        wait(0);
    }
}
void sighan(int s)
{
    kill(getppid(), SIGTERM);
}

int main()
{
    signal(SIGTERM, sighan);
    FILE *fptr;
    char file_content;

    int iterator;
    do
    {
        char user[20];
        char password[20];
        char correct_user[20];
        char correct_password[20];
        printf("\nLogin:");
        scanf("%s", user);
        fflush(stdout);

        printf("\nPassword:");
        scanf("%s", password);
        fflush(stdout);

        if ((fptr = fopen("passwd.txt", "r")) == NULL)
        {
            printf("Cannot open file \n");
            exit(0);
        }

        file_content = fgetc(fptr);
        while (file_content != EOF)
        {
            iterator = 0;
            while (file_content != 58)
            {
                if (file_content == EOF)
                {
                    break;
                }
                if (file_content != '\n')
                {
                    correct_user[iterator] = file_content;
                    iterator++;
                    file_content = fgetc(fptr);
                }
            }
            correct_user[iterator] = '\0';

            if (file_content == EOF)
            {
                break;
            }
            file_content = fgetc(fptr);
            iterator = 0;

            while (file_content != '\n')
            {
                if (file_content == EOF)
                {
                    break;
                }
                correct_password[iterator] = file_content;
                iterator++;
                file_content = fgetc(fptr);
            }
            correct_password[iterator] = '\0';
            file_content = fgetc(fptr);
            if (strcmp(user, correct_user) == 0 && strcmp(password, correct_password) == 0)
            {
                login();
            }
        }
    } while (1);

    fclose(fptr);
}