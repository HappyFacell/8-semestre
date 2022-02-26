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

void *calcularPrimos(void *n_arg);
int isprime(int n);

struct argus
{
    int i;
    int min;
    int max;
};

int main(int argc, char *argv[])
{

    struct argus argsx;
    pthread_t tid[NTHREADS];

    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    argsx.min = min;
    argsx.max = max;

    printf("min: %d max: %d\n", min, max);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    pthread_mutex_init(&g_cs, NULL);
    long num;
    for (int i = 0; i < NTHREADS; i++)
    {
        argsx.i = i;
        pthread_create(&tid[i], NULL, calcularPrimos, &argsx.i);
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

void *calcularPrimos(void *n_arg)
{
    struct argus *argsx = n_arg;

    int count = 0;
    int start = argsx->i * (argsx->min / NTHREADS); //1 
    int end = start + (argsx->max / NTHREADS);

    for (int i = start; i <= end; i++)
    {
        if (isprime(i))
        {
            pthread_mutex_lock(&g_cs);
            totalSum++;
            pthread_mutex_unlock(&g_cs);
        }
    }
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