#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define ITERACIONES 2000000000
#define NPROCS 4

void calcularPi(int n_arg);
double *sharedmem;

int main()
{

    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    struct timeval ts;

    int i;
    long num;
    double pi;
    int status;
    int shmid;
    int pid;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    shmid = shmget(0x1234, NPROCS * sizeof(double), IPC_CREAT | 0666); // Obtener memoria compartida
    if (shmid < 0)
    {
        fprintf(stderr, "Error al obtener memoria compartida\n");
        exit(1);
    }
    sharedmem = shmat(shmid, NULL, 0);

    // fork para cada proceso heredan  la variable que esta conectada a la memoria compartida
    for (i = 0; i < NPROCS; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            calcularPi(i);
        }
    }

    for (i = 0; i < NPROCS; i++)
    {
        wait(&status);
    }
    for (i = 0; i < NPROCS; i++)
    {
        pi += sharedmem[i];
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    pi = pi * 4;

    printf("PI = %1.20lf\n", pi);

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);

    shmdt(sharedmem);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

void calcularPi(int n_arg)
{
    int i;
    int num = n_arg;

    double num_elevado;
    double sum = 0.0;
    int start = num * (ITERACIONES / NPROCS);
    int end = start + (ITERACIONES / NPROCS);

    for (i = start; i < end; i++)
    {
        num_elevado = pow(-1, i);
        sum += (num_elevado / (2 * i + 1));
    }

    sharedmem[num] = sum;
    exit(1);
}