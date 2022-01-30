/* programa que será invocado desde los ejemplos 11,12 y 13 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	sleep(10);
	printf("Hola mundo, soy el proceso %d\n",getpid());
	sleep(10);
	printf("Proceso acabado\n");
	return 0;
}