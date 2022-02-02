#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define TAM 2000

int A[TAM][TAM];
int B[TAM][TAM];
int C[TAM][TAM];

int main()
{
	int i,j,k;
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial
	
	for(i=0;i<TAM;i++)
		for(j=0;j<TAM;j++)
			for(k=0;k<TAM;k++)
				C[i][j]=C[i][j]+A[i][k]*B[k][j];
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %d segundos\n",(int) elapsed_time);
}