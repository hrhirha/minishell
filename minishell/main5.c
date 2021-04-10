/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/17 17:37:12 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func4(t_minishell *minishell, t_command *command)
{
	int	status;

	status = shell_execute(minishell, command);
	if (status == 1)
		exit(0);
	exit (status);
	return (1);
}

int	func5(int **pipes_fd, int *forks)
{
	ft_putstr_fd("minishell: Error in pipe\n", 2);
	free(forks);
	free_double_int(pipes_fd);
	return (1);
}

int	func6(int **pipes_fd, int *forks, int commands_len)
{
	int	j;

	j = 0;
	while (j < (commands_len - 1))
	{
		pipes_fd[j] = malloc(2 * sizeof(int));
		if (pipe(pipes_fd[j]) == -1)
		{
			free(pipes_fd);
			free(forks);
			ft_putstr_fd("minishell: Error in pipe\n", 2);
			return (1);
		}
		j++;
	}
	pipes_fd[j] = NULL;
	return (0);
}

int	func7(t_minishell *minishell, t_helper1 helper, int i)
{
	int	status;

	helper.forks[i] = fork();
	g_exist.pid = 1;
	if (helper.forks[i] < 0)
		return (func5(helper.pipes_fd, helper.forks));
	if (helper.forks[i] == 0)
	{
		func2(i, helper.pipes_fd, helper.commands_len);
		status = func3(minishell, helper.command,
				helper.pipes_fd, helper.forks);
		if (status != 0)
			return (status);
		status = func4(minishell, helper.command);
		if (status == 0)
			return (0);
	}
	return (99);
}

int	commands_loop(t_minishell *minishell, t_list *my_pipe)
{
	t_list		*current;
	int			status;
	t_helper1	helper;
	int			i;

	helper.commands_len = ft_lstsize(my_pipe);
	helper.forks = malloc((helper.commands_len + 1) * (sizeof(int)));
	helper.pipes_fd = malloc((helper.commands_len + 1) * (sizeof(int *)));
	status = func6(helper.pipes_fd, helper.forks, helper.commands_len);
	if (status == 1)
		return (1);
	current = my_pipe;
	i = 0;
	while (current != NULL)
	{
		helper.command = (t_command *)current->content;
		status = func7(minishell, helper, i);
		if (status != 99)
			return (status);
		i++;
		current = current->next;
	}
	func1(helper.pipes_fd, helper.forks, helper.commands_len);
	return (1);
}
