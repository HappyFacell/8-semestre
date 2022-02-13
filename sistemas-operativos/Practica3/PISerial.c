#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define ITERACIONES 2000000000

double calcularPi(double iteraciones);

int main()
{
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    struct timeval ts;
    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial
    double pi = calcularPi(ITERACIONES);
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;
    printf("PI = %lf\n", pi);
    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
double calcularPi(double iteraciones)
{
    int i;
    double sum = 0;
    double num_elevado, pi;

    for (i = 0; i < ITERACIONES; i++)
    {
        pi += (pow(-1, i) / (2 * i + 1));
    }
    return pi * 4;
}