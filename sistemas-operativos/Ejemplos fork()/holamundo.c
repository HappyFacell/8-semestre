/* programa que será invocado desde los ejemplos 11,12 y 13 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Hola mundo, soy el proceso %d\n",getpid());
	return 0;
}