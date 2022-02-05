#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_handler()
{
	/*do something*/
	printf("killing process %d\n", getpid());
	exit(0);
}

int main()
{
	int num_children = 4;
	int i, pid, status;
	printf("This is the parent. PID=%d\n", getpid());

	while (1)
	{
		for (i = 0; i < num_children; i++)
		{
			if ((pid = fork()) == 0)
			{
				signal(SIGINT, sigint_handler);
				printf("This is children %d\n", getpid());
				sleep(1);
				exit(0);
			}
		}

		// Rest Parent code
		sleep(1);
		waitpid(pid, &status, 0);
		printf("This is the parent again %d, children should have finished\n", getpid());
	}
}