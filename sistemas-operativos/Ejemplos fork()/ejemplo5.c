#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int g=10;

int main()
{
	pid_t p;
	
	p=fork();
	
	if(p!=0) // El padre
	{
		g++;
		printf("En el padre g=%d\n",g);
		sleep(1);
	} 
	else
	{
		sleep(1);
		g=g-2;
		printf("En el hijo g=%d\n",g);
	}
	return 0;
}