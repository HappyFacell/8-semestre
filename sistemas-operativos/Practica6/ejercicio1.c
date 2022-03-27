#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "semaphores.h"

#define TAMBUFFER 10

#define VELPROD 500000 // Microsegundos
#define VELCONS 100000
#define NPRODS 4

#define LIMITE 100

struct node
{
    int primNumber;
    struct node *next;
};

struct STRBUFF
{
    int ent; // Donde va a estar el siguiente elemento que voy a meter al buffer
    int sal;
    int count;                      // Donde está el siguiente elemento que voy a sacar del buffer
    unsigned int buffer[TAMBUFFER]; // Buffer circular
};

typedef struct node primeNode;

primeNode *createNode();
primeNode *head = NULL;

struct STRBUFF *bf;

void productor(int args);
void consumidor();
int isprime(int n);
void addPrimeNumber(int num);
void printList();
void bubbleSort(primeNode *start);
void swap(primeNode *a, primeNode *b);

SEM_ID semarr;
enum
{
    E_MAX,
    N_BLOK,
    S_EXMUT,
    S_STOP
}; // Semáforos 0,1 y 2

int max = 0;
int min = 0;

int main(int argc, char *argv[])
{
    // Definición de variables
    int i;
    int res;
    int n;
    int p;
    int shmid;
    int pid;

    srand(getpid());

    min = atoi(argv[1]);
    max = atoi(argv[2]);

    printf("min: %d max: %d\n", min, max);

    head = (primeNode *)malloc(max * sizeof(struct node));

    // Creación del arreglo de semáforos
    semarr = createsemarray((key_t)0x1234, 3);

    initsem(semarr, E_MAX, TAMBUFFER);
    initsem(semarr, N_BLOK, 0);
    initsem(semarr, S_EXMUT, 1);

    // Crear la memoria compartida
    // Solicitar memoria compartida para el buffer
    shmid = shmget((key_t)0x1234, sizeof(struct STRBUFF), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "Error al solicitar memoria compartida\n");
        exit(1);
    }
    bf = shmat(shmid, NULL, 0);
    bf->ent = 0;
    bf->sal = 0;
    bf->count = 0;

    /* Aquí se crean los procesos */
    for (i = 0; i < NPRODS; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            productor(i);
        }
    }

    p = fork();
    if (p == 0)
    {
        consumidor();
    }

    for (n = 0; n <= NPRODS; n++)
        wait(NULL);

    // Borrar los semáforos

    erasesem(semarr, E_MAX);
    erasesem(semarr, N_BLOK);
    erasesem(semarr, S_EXMUT);

    shmdt(bf);                     // Desconectar la memoria compartida al terminar
    shmctl(shmid, IPC_RMID, NULL); // Pedir al SO que elimine la memoria compartida

    exit(EXIT_SUCCESS);
}

void productor(int args)
{

    int nprocs = args;
    int start = nprocs * (max / NPRODS);
    int end = start + (max / NPRODS);

    int n;

    printf("Inicia productor\n");
    for (n = start; n <= end; n++)
    {
        if (isprime(n) || n == end)
        {
            semwait(semarr, E_MAX);   // Si se llena el buffer se bloquea
            semwait(semarr, S_EXMUT); // Asegurar el buffer como sección crítoca

            if (n != end)
            {
                bf->buffer[bf->ent] = n;
                printf("Productor produce %d\n", n);
            }
            else
            {
                bf->count++;
                // printf("%d\n", bf->count);
                if (bf->count == NPRODS)
                    bf->buffer[bf->ent] = 0;
            }
            bf->ent++;
            if (bf->ent == TAMBUFFER) // Si TAMBUFFER es 5, 0 1 2 3 4
                bf->ent = 0;

            usleep(rand() % VELPROD);

            semsignal(semarr, S_EXMUT); // Libera la sección crítica del buffer
            semsignal(semarr, N_BLOK);  // Si el consumidor está bloqueado porque el buffer está vacío, lo desbloqueas

            usleep(rand() % VELPROD);
        }
    }
    exit(0);
}

void consumidor()
{
    int n = 1;
    printf("Inicia Consumidor\n");
    while (n)
    {
        semwait(semarr, N_BLOK);  // Si el buffer está vacío, se bloquea
        semwait(semarr, S_EXMUT); // Asegura el buffer como sección crítica

        n = bf->buffer[bf->sal];
        // printf("\t\tn: %d\n", n);
        if (n)
        {
            printf("\tConsumidor consume %d\n", n);
            addPrimeNumber(n);
        }
        bf->sal++;
        if (bf->sal == TAMBUFFER)
            bf->sal = 0;

        usleep(rand() % VELCONS);

        semsignal(semarr, S_EXMUT); // Libera la SC el buffer
        semsignal(semarr, E_MAX);   // Si el productor está bloqueado porque el buffer estaba lleno, lo desbloquea
        usleep(rand() % VELCONS);
    }
    printList();
    exit(0);
}

void printList()
{
    printf("Soy un print :3\n");
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

    /* Checking for empty list */
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

primeNode *createNode()
{
    primeNode *temp;
    temp = (primeNode *)malloc(sizeof(struct node));
    temp->next = NULL;
    return temp;
}

void addPrimeNumber(int num)
{
    primeNode *temp, *newNode;
    newNode = createNode(); //(primeNode*)malloc(sizeof(struct node));
    temp = head;
    // printf("addPrimeNumber: %d\n", num);
    newNode->primNumber = num;
    newNode->next = NULL;
    // printf("primNumber: %d\n", newNode->primNumber);

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
    // printf("temp: %d\n", temp->next->primNumber);

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