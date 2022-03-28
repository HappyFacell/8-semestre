#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>

#define NPRODS 4

struct msgbuf
{
    long mtype;
    char mtext[30];
};

int queue;

struct Args
{
    int i;
    int min;
    int max;
};

struct node
{
    int primNumber;
    struct node *next;
};

typedef struct node primeNode;

primeNode *createNode(int max);
primeNode *head = NULL;

struct STRBUFF *bf;

int isprime(int n);
void addPrimeNumber(int num, int max);
void printList();
void bubbleSort(primeNode *start);
void swap(primeNode *a, primeNode *b);

void emisor();
void receptor();
int isprime(int n);

int main(int argc, char *argv[])
{
    int min, max, i;
    int pid;
    int status;

    struct Args intvar;

    min = strtol(argv[1], NULL, 10);

    max = strtol(argv[2], NULL, 10);

    intvar.min = min;

    intvar.max = max;

    queue = msgget(0x1234, 0666 | IPC_CREAT);
    if (queue == -1)
    {
        fprintf(stderr, "No se pudo crear el buzón\n");
        exit(1);
    }

    for (i = 0; i < NPRODS; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            intvar.i = i;
            emisor(intvar);
        }
    }
    pid = fork();
    if (pid == 0)
        receptor(max);

    for (int n = 0; n <= NPRODS; n++)
        wait(NULL);

    msgctl(queue, IPC_RMID, NULL);
}

void emisor(struct Args variables)
{
    int num = variables.i;
    int min = variables.min;
    int max = variables.max;
    int start = num * (max / NPRODS);
    int end = start + (max / NPRODS);
    int i;
    struct msgbuf mensaje;
    for (i = start; i <= end; i++)
    {
        mensaje.mtype = 1;
        if (isprime(i))
        {
            sprintf(mensaje.mtext, "%d", i);
            msgsnd(queue, &mensaje, sizeof(struct msgbuf), IPC_NOWAIT); // No espera a que sea recibido
            sleep(1);
        }
    }

    sprintf(mensaje.mtext, "-1");
    msgsnd(queue, &mensaje, sizeof(struct msgbuf), IPC_NOWAIT);
    exit(0);
}

void receptor(int max)
{
    struct msgbuf mensaje;
    int status;
    do
    {
        status = msgrcv(queue, &mensaje, sizeof(struct msgbuf), 1, IPC_NOWAIT);
        if (status != -1)
        {
            addPrimeNumber(atoi(mensaje.mtext), max);
        }

        usleep(200000);
    } while (strcmp(mensaje.mtext, "-1") != 0);
    printList();
    exit(0);
}

void printList()
{
    bubbleSort(head);
    head = head->next;
    while (head != NULL)
    {
        printf("%d\n", head->primNumber);
        head = head->next;
    }
}

void bubbleSort(primeNode *start)
{
    int swapped, i;
    primeNode *ptr1;
    primeNode *lptr = NULL;

    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->primNumber > ptr1->next->primNumber)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void swap(primeNode *a, primeNode *b)
{
    int temp = a->primNumber;
    a->primNumber = b->primNumber;
    b->primNumber = temp;
}

primeNode *createNode(int max)
{
    primeNode *temp;
    temp = (primeNode *)malloc(sizeof(struct node));
    temp->next = NULL;
    return temp;
}

void addPrimeNumber(int num, int max)
{
    primeNode *temp, *newNode;
    newNode = createNode(max);
    temp = head;
    newNode->primNumber = num;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    while ((temp)->next != NULL)
    {
        temp = (temp)->next;
    }

    (temp)->next = newNode;

    return;
}

int isprime(int n)
{
    int d = 3;
    int prime = 0;
    int limit = sqrt(n);

    if (n < 2)
        prime = 0;
    else if (n == 2)
        prime = 1;
    else if (n % 2 == 0)
        prime = 0;
    else
    {
        while (d <= limit && n % d)
            d += 2;
        prime = d > limit;
    }
    return (prime);
}