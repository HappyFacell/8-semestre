#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

double calcularPi(double iteraciones)
{
    long int i;

    double aux;
    double pi = 0;

    for (i = 0; i < iteraciones; i++)
    {
        aux = pow(-1, i) / (2 * i + 1);

        pi += aux;
    }
    return pi * 4;
}

int main()
{
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    struct timeval ts;
    double iteraciones = 2000000000;
    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial
    double pi = calcularPi(iteraciones);
    printf("PI = %1.20lf\n", pi);
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}