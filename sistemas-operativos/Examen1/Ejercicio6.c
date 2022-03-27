#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define NTHREADS 4

pthread_mutex_t g_cs;

int totalSum = 0;
int max;
int min;

void *calcularPrimos(void *args);
int isprime(int n);


int main(int argc, char *argv[])
{

    pthread_t tid[NTHREADS];
    int args[NTHREADS];

    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    min = atoi(argv[1]);
    max = atoi(argv[2]);

    printf("min: %d max: %d\n", min, max);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    pthread_mutex_init(&g_cs, NULL);
    long num;
    for (int i = 0; i < NTHREADS; i++)
    {
        args[i] = i;
        pthread_create(&tid[i], NULL, calcularPrimos, &args[i]);
    }
    pthread_mutex_destroy(&g_cs);

    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;
    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
    printf("\n Num primos = %d\n", totalSum);
    return 0;
}

void *calcularPrimos(void *args)
{
    int nthread = *((int *)args);

    int start = nthread * (max / NTHREADS); // 1
    int end = nthread + (max / NTHREADS);
    int count = 0;

    for (int i = nthread; i <= max; i += NTHREADS)
    {
        if (isprime(i))
        {
            count++;
            printf("i: %d\n", i);
        }
    }
    pthread_mutex_lock(&g_cs);
    totalSum += count;
    pthread_mutex_unlock(&g_cs);
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