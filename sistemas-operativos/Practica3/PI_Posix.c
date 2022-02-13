#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define NTHREADS 4
#define ITERACIONES 2000000000

void *pi_thread(void *args);

double sum[NTHREADS];
double pi = 0.0;

int main()
{

    pthread_t tid[NTHREADS];
    int args[NTHREADS];

    long long start_ts;
    long long stop_ts;
    long long elapsed_time;

    struct timeval ts;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec;

    // se crean los threads y empiezan a calcular pi

    for (int i = 0; i < NTHREADS; i++)
    {
        sum[i] = 0;
        args[i] = i;
        pthread_create(&tid[i], NULL, pi_thread, &args[i]);
    }

    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < NTHREADS; i++)
        pi = pi + sum[i];

    pi = 4 * pi;

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec;
    elapsed_time = stop_ts - start_ts;

    printf("PI = %1.20lf\n", pi);

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}

void *pi_thread(void *args)
{
    int tnum = *((int *)args);
    long int i;

    double term;

    for (i = tnum; i < ITERACIONES; i += NTHREADS)
    {
        term = pow(-1, i) / (2 * i + 1);

        sum[tnum] += term;
    }
}
