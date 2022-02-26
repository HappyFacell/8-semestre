#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/time.h>
int main(int argc, char *argv[])
{
    int min, max, temp, count = 0, i, j;
    long long start_ts;
    long long stop_ts;
    int elapsed_time;
    long lElapsedTime;
    struct timeval ts;
    min = strtol(argv[1], NULL, 10);
    max = strtol(argv[2], NULL, 10);
    printf("min: %d max: %d\n", min, max);
    /* Generating and counting prime numbers */
    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial
    for (i = min; i <= max; i++)
    {
        temp = 0;
        for (j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                temp = 1;
                break;
            }
        }
        if (temp == 0 && i >= 2)
        {

            count++;
        }
    }
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final
    elapsed_time = (int)(stop_ts - start_ts);
    printf("proceso %d, %d microsegundos\n", getpid(), elapsed_time);
    printf("\n Num primos = %d\n", count);
    return 0;
}