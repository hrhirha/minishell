#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		stat;

	if (ac >= 2)
	{
		if ((pid = fork()) == 0)
		{
			if (strcmp(av[1], "ls") == 0)
			{
				execve("/bin/ls", &av[1], env);
			}
			else
				printf("command not found\n");
		}
		wait(&stat);
	}
	else
		printf("At least one argument shoud be present\n");
}
