#include <stdio.h>
#include <curses.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define NUMTHREADS 4
#define SERIES_MEMBER_COUNT 500000000

HANDLE *threadHandles, masterThreadHandle;
CRITICAL_SECTION countCS;
double *sums;
double x = 1.0, res = 0.0;

double getMember(int n, double x, double *numerator)
{
    if (n > NUMTHREADS)
    {
        for (int i = 0; i < NUMTHREADS; i++)
            *numerator = (*numerator) * x;
    }

    if (n % 2 == 0)
    {
        return (-(*numerator) / n);
    }
    else
    {
        return (*numerator) / n;
    }
}

DWORD WINAPI threadProc(LPVOID par)
{
    int threadIndex = *((int *)par);
    double temp_sum = 0;
    double numerator = 1;

    for (int i = 0; i < threadIndex + 1; i++)
    {
        numerator = numerator * x;
    }

    for (int i = threadIndex; i < SERIES_MEMBER_COUNT; i += NUMTHREADS)
    {
        temp_sum += getMember(i + 1, x, &numerator);
    }

    sums[threadIndex] = temp_sum;
    return 0;
}

void main()
{
    threadHandles = malloc((NUMTHREADS) * sizeof(HANDLE));
    sums = malloc(sizeof(double) * NUMTHREADS);
    clock_t start, stop;
    start = clock();
    for (int i = 0; i < NUMTHREADS; i++)
    {
        int *threadIdPtr = malloc(sizeof(int));
        *threadIdPtr = i;
        threadHandles[i] = CreateThread(NULL, 0, threadProc, threadIdPtr, 0, NULL);
    }

    printf("Count of ln(1 + x) Mercator's series members is %d\n", SERIES_MEMBER_COUNT);
    printf("Argument value of x is %f\n", (double)x);
    WaitForMultipleObjects(NUMTHREADS + 1, threadHandles, TRUE, INFINITE);
    res = 0;
    for (int i = 0; i < NUMTHREADS; i++)
    {
        res += sums[i];
    }

    stop = clock();

    printf("Tiempo = %2.7f\n", (float)(stop - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < NUMTHREADS + 1; i++)
        CloseHandle(threadHandles[i]);

    free(threadHandles);
    free(sums);
    printf("Result is %10.8f\n", res);
    printf("By function call ln(1 + %f) = %10.8f\n", x, log(1 + x));
    printf("Press any key ... ");
    _getch();
}