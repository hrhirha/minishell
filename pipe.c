#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include <sys/wait.h>

void	ft_exec(char *s)
{
	char **cmd;

	cmd = ft_split(s, ' ');
	if (strcmp(cmd[0], "ls") == 0)
		execve("/bin/ls", cmd, NULL);
	else if (strcmp(cmd[0], "wc") == 0)
		execve("/usr/bin/wc", cmd, NULL);
	else if (strcmp(cmd[0], "cat") == 0)
		execve("/bin/cat", cmd, NULL);
	else if (strcmp(cmd[0], "grep") == 0)
		execve("/usr/bin/grep", cmd, NULL);
	else if (strcmp(cmd[0], "cd") == 0)
		execve("/usr/bin/cd", cmd, NULL);
}

void	pipelines(int ispipe, char *s, int pid, int *fd)
{
	int		i;
	char	**tab;

	tab = ft_split(s, '|');
	i = 0;
	while (tab[i])
	{
		if (pid == 0)
		{
			if (pipe(fd) == -1)
				exit(1);
			if ((pid = fork()) > 0)
			{
				if (ispipe > 0)
					dup2(fd[1], 1);
				ft_exec(tab[i]);
			}
			else if (pid == 0)
				dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		i++;
		ispipe--;
	}
}

int		main(int ac, char **av)
{
	int		i;
	int		ispipe;
	pid_t	pid;
	int		*fd;
	int		stat;

	fd = malloc(2 * sizeof(int));
	ispipe = 0;
	if  (ac >= 2)
	{
		i = 0;
		while (av[1][i])
		{
			if (av[1][i] == '|')
				ispipe++;
			i++;
		}
		if ((pid = fork()) == 0)
		{
			if (ispipe > 0)
				pipelines(ispipe, av[1], pid, fd);
			else
				ft_exec(av[1]);
		}
		else
			printf("pid exit %d with stat = %d\nchild pid = %d\n", (int)wait(&stat), stat, pid);
	}
	else
		printf("More arguments required\n");
}
