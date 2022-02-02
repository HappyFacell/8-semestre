#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define TAM 2000
#define NTHREADS 4

int A[TAM][TAM];
int B[TAM][TAM];
int C[TAM][TAM];

void *tfunc(void *args)
{
	int nthread=*((int *) args);
	int i,j,k;
	int inicio=nthread*(TAM/NTHREADS);
	int fin=(nthread+1)*(TAM/NTHREADS);
	
	for(i=inicio;i<fin;i++)
		for(k=0;k<TAM;k++)
			for(j=0;j<TAM;j++)
				C[i][j]=C[i][j]+A[i][k]*B[k][j];

}

int main()
{
	int i;
	int parArr[NTHREADS];
	pthread_t tid[NTHREADS];
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	// Crear los hilos
	for(i=0;i<NTHREADS;i++)
	{
		parArr[i]=i;
		pthread_create(&tid[i],NULL,tfunc,(void *) &parArr[i]);
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %d segundos\n",(int) elapsed_time);
}