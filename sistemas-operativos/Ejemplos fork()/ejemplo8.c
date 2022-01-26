#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NPROCS 4

void proc(int n);

int main()
{
	int i;
	pid_t p;
	int status;
	
	for(i=0;i<NPROCS;i++)
	{
		p=fork();
		if(p==0)
			proc(i);
	}	
	
	for(i=0;i<NPROCS;i++)
		wait(&status);
}

void proc(int n)
{
	printf("Soy el proceso hijo %d, mi pid es %d\n",n,getpid());
	exit(0);
}