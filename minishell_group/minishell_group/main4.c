/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/14 16:59:43 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		loop_redirections2(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == LEFT_REDIR)
	{
		fd = read_file(redirection->file_name);
		if (fd < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		if (redirection->type == RIGHT_REDIR)
			fd = create_empty_file(redirection->file_name);
		else
			fd = create_append_file(redirection->file_name);
		if (fd < 0)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int		loop_redirections(t_minishell *minishell, t_command *command)
{
	t_list			*current;
	t_redirection	*redirection;
	int				status;
	int				fd;

	status = 1;
	current = command->redirections;
	while (current != NULL)
	{
		redirection = (t_redirection*)current->content;
		status = loop_redirections2(redirection);
		if (status != 0)
			return (status);
		current = current->next;
	}
	if (command->full_args == NULL)
		reset_std(minishell);
	return (1);
}

void	func1(int **pipes_fd, int *forks, int commands_len)
{
	int	f;

	f = 0;
	while (f < (commands_len - 1))
	{
		close(pipes_fd[f][0]);
		close(pipes_fd[f][1]);
		f++;
	}
	f = 0;
	while (f < commands_len)
	{
		waitpid(forks[f], &g_exist.last_exec, 0);
		g_exist.last_exec = WEXITSTATUS(g_exist.last_exec);
		f++;
	}
	free(forks);
	free_double_int(pipes_fd);
}

void	func2(int i, int **pipes_fd, int commands_len)
{
	int f;

	if (i == 0)
		dup2(pipes_fd[0][1], 1);
	else if (i == (commands_len - 1))
		dup2(pipes_fd[i - 1][0], 0);
	else
	{
		dup2(pipes_fd[i - 1][0], 0);
		dup2(pipes_fd[i][1], 1);
	}
	f = 0;
	while (f < (commands_len - 1))
	{
		close(pipes_fd[f][0]);
		close(pipes_fd[f][1]);
		f++;
	}
}

int		func3(t_minishell *minishell, t_command *command,
		int **pipes_fd, int *forks)
{
	int status;

	status = loop_redirections(minishell, command);
	if (status < 0)
	{
		exit(1);
		return (-1);
	}
	else if (status == 0)
	{
		free(forks);
		free_double_int(pipes_fd);
		return (1);
	}
	return (0);
}
