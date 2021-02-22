#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int		main(void)
{
	int		stat;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		printf("Hello From CHILD\n");
	}
	else
	{
		printf("PARENT waiting for child to die\n");
		wait(&stat);
		printf("child is dead, stat = %d\n", stat);
	}
}
