#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int		main(void)
{
	pid_t pid;
	int i = 0;
	int stat;

	if ((pid = fork()) != 0)
	{
		sleep(1);
		wait(&stat);
		printf("All Children have been killed %d\n", stat);
	}
	while (i < 5)
	{
		if (pid == 0)
		{
			if ((pid = fork()) == 0)
				;//printf("CHILD number %d with pid = %d\n", i, (int)pid);
			else
				printf("PARENT number %d with child's pid = %d\n", i, (int)pid);
		}
		i++;
	}
}
