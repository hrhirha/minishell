/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 16:08:00 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_loop2(t_minishell *minishell, t_list *my_pipe)
{
	int			status;
	t_command	*command;

	status = 1;
	command = (t_command *)my_pipe->content;
	status = loop_redirections(minishell, command);
	if (status < 0)
		return (1);
	status = shell_execute(minishell, command);
	if (status == 0)
		return (0);
	reset_std(minishell);
	return (1);
}

int	pipes_loop(t_minishell *minishell)
{
	t_list	*current;
	int		status;
	t_list	*my_pipe;

	status = 1;
	current = minishell->cmds;
	while (current != NULL)
	{
		my_pipe = current->content;
		scan_command(my_pipe, minishell->env);
		if (my_pipe->next == NULL)
			status = commands_loop2(minishell, my_pipe);
		else
			status = commands_loop(minishell, my_pipe);
		if (status < 0)
		{
			g_exist.last_exec = 1;
			return (1);
		}
		else if (status == 0)
			return (0);
		current = current->next;
	}
	return (1);
}
