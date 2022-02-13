#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#define ITERACIONES 2000000000
#define NTHREADS 4

pthread_mutex_t g_cs;
double sum;

void *pi_thread(void *n_arg);

int main()
{
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    struct timeval ts;

    int i;
    int args[NTHREADS];
    pthread_t tid[NTHREADS];
    double pi;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    pthread_mutex_init(&g_cs, NULL);
    for (i = 0; i < NTHREADS; i++)
    {
        args[i] = i;
        pthread_create(&tid[i], NULL, pi_thread, &args[i]);
    }
    pthread_mutex_destroy(&g_cs);

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    pi = sum * 4;

    printf("PI = %1.20lf\n", pi);

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);

    return 0;
}

void *pi_thread(void *args)
{
    int nthread = *((int *)args);
    double aux;
    int start = nthread * (ITERACIONES / NTHREADS);
    int end = start + (ITERACIONES / NTHREADS);

    for (int i = start; i < end; i++)
    {
        aux += (pow(-1, i) / (2 * i + 1));
    }
    pthread_mutex_lock(&g_cs);
    sum += aux;
    pthread_mutex_unlock(&g_cs);
}