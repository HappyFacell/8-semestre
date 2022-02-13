#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define ITERACIONES 2000000000
#define NPROCS 4

void pi_fork(int args);
double *SharedMemSum;

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
    
    // Se emplea en la creación o acceso a una zona de memoria compartida
    shmid = shmget(0x1234, NPROCS * sizeof(double), IPC_CREAT | 0660); // Obtener memoria compartida
    //-1 si ha habido error
    if (shmid < 0)
    {
        fprintf(stderr, "Error al obtener memoria compartida\n");
        exit(1);
    }
    /*
    Para acceder a memoria compartida previamente creada,
    es necesario que alguna variable del
    proceso «apunte» a esa zona de memoria que no pertenece a
    su espacio de direccionamiento.
    */
    SharedMemSum = shmat(shmid, NULL, 0);

    // fork para cada proceso heredan  la variable que esta conectada a la memoria compartida
    for (i = 0; i < NPROCS; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            pi_fork(i);
        }
    }

    for (i = 0; i < NPROCS; i++)
    {
        wait(&status);
    }
    for (i = 0; i < NPROCS; i++)
    {
        pi += SharedMemSum[i];
    }
    pi = pi * 4;

    /*
        separa del espacio de direcciones del
        proceso de llamada el segmento de memoria
        compartida ubicado en la dirección
        */
    shmdt(SharedMemSum);
    // liberar la memoria compartida
    shmctl(shmid, IPC_RMID, NULL);

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("PI = %lf\n", pi);

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);

    return 0;
}

void pi_fork(int args)
{
    int i;
    int nprocs = args;

    double sum = 0;
    int start = nprocs * (ITERACIONES / NPROCS);
    int end = start + (ITERACIONES / NPROCS);

    for (i = start; i < end; i++)
    {
        sum += (pow(-1, i) / (2 * i + 1));
    }

    SharedMemSum[nprocs] = sum;
    exit(1);
}