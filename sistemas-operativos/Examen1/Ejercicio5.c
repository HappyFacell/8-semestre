#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/time.h>
int main(int argc, char *argv[])
{
    long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

    int min; 
    int max;
    int temp;
    int count = 0;


    min = strtol(argv[1], NULL, 10);
    max = strtol(argv[2], NULL, 10);
    printf("min: %d max: %d\n", min, max);

    /* Generating and counting prime numbers */
    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    for (int i = min; i <= max; i++)
    {
        temp = 0;
        for (int j = 2; j <= i / 2; j++)
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
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
    printf("\n Num primos = %d\n", count);
    return 0;
}
