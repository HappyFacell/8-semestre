#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 2

void myprint(char *s)
{
	usleep(rand()%10000);
	printf("%s\n",s);
	return;
}

void *p(void *args)
{
	myprint("A");
	myprint("B");
	myprint("C");
}

void *q(void *args)
{
	myprint("\tD");
	myprint("\tE");

}

int main()
{
	int i;
	pthread_t tid[NTHREADS];

	srand(getpid());
	
	pthread_create(&tid[0],NULL,p,NULL);
	pthread_create(&tid[1],NULL,q,NULL);
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);
}