#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t p;
	int i;
	int inicio=10;
	int max=inicio+10;
	int min=inicio-10;

	p=fork();
	
	if(p==0)	// En el hijo
	{
		for(i=inicio;i<max;i++)
		{
			printf("Hijo i=%d\n",i);
			sleep(1);
		}
	}
	else // En el padre
	{
		for(i=inicio;i>min;i--)
		{
			printf("Padre i=%d\n",i);
			sleep(1);
		}
	}
	return 0;
}