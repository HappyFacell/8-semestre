#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 5

#define FALSE 0
#define TRUE 1

int seleccionando[NTHREADS]={FALSE,FALSE,FALSE,FALSE,FALSE};
int numero[NTHREADS]={0,0,0,0,0};

void cs(int i);
void rs();
int maxnum(int *nums);

void *tfunc(void *args)
{
	int i=*((int *) args);
	int j;
	
	int n;
	
	for(n=0;n<10;n++)
	{
		rs();
		// Sección de entrada
		seleccionando[i]=TRUE;
		numero[i]=maxnum(numero)+1;	//Obtener mi número de turno
		seleccionando[i]=FALSE;
		
		// Ver si no hay otros que tengan un número antes que el mio
		for(j=0;j<NTHREADS;j++)
		{
			while(seleccionando[j]); // Si j está seleccionando me espero
			while(numero[j]!=0 && (numero[j]<numero[i] || numero[j]==numero[i] && j<i));
		}
		
		cs(i);
		
		numero[i]=0;
		
		rs();
	}
	
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];
	int pargs[NTHREADS];
	
	for(i=0;i<NTHREADS;i++)
	{
		pargs[i]=i;
		pthread_create(&tid[i],NULL,tfunc,&pargs[i]);
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);
}

void cs(int i)
{
	printf("%d entra a la sección crítica\n",i);
	usleep(250000);
	printf("%d sale de la sección crítica\n",i);
}
void rs()
{
	usleep(250000);
}

int maxnum(int *nums)
{
	int m=0;
	int i;
	for(i=0;i<NTHREADS;i++)
		if(nums[i]>m)
			m=nums[i];
	return(m);
}