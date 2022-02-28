#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/time.h>

int isprime(int n);

int main(int argc, char *argv[])
{

    int count = 0;

    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    printf("min: %d max: %d\n", min, max);
    
    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial
    for (int i = min; i <= max; i++)
    {
        if (isprime(i))
        {
            count++;
        }
    }
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;
    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
    printf("\n Num primos = %d\n", count);
    return 0;
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