#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double calcularPi(double iteraciones)
{
    double numerador = 4;
    double denominador = 1;
    double pi = 0;
    int x = 0;
    int operador = 1;
    for (x; x < iteraciones; x++)
    {
        pi += operador * (numerador / denominador);
        denominador += 2;
        operador *= -1;
    }
    return pi;
}

int main()
{
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
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