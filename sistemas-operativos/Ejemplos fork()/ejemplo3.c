#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;
	
	for(i=0;i<5;i++)
	{
		fork();
		printf("%d\n",i);
	}
}