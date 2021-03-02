/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:52:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/01 09:52:14 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redir(t_list *redirs)
{
	t_list			*tmp;
	t_redirection	redir;

	while (redirs)
	{
		redir = *(t_redirection *)redirs->content;
		printf("[%d]file = `%s`\n",  redir.type,redir.file_name);
		free(redir.file_name);
		tmp = redirs->next;
		free(redirs->content);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmd(t_command *command, t_data *data)
{
	int				j;
	t_list			*tmp_redir;

	(void)data;
	j = 0;
	tmp_redir = command->redirections;
	free_redir(tmp_redir);
	if (*command->cmd)
	{
		printf("cmd = `%s`\n", command->cmd);
		if (command->full_args == NULL)
			;
		else
		{
			while (command->full_args[j])
			{
				printf("arg[%d] = `%s`\n", j, command->full_args[j]);
				free(command->full_args[j++]);
			}
			free(command->full_args);
		}
	}
	free(command->cmd);
}

void	free_pipes(t_list *pipes, t_data *data)
{
	t_command		command;
	t_list			*tmp;

	while (pipes)
	{
		command = *(t_command *)pipes->content;
		free_cmd(&command, data);
		tmp = pipes->next;
		free(pipes->content);
		free(pipes);
		pipes = tmp;
		// printf("Next pipe\n");
	}
}

void	free_last_cmd(t_data *data)
{
	printf("freeing data, line is Empty\n");
	// printf("cmd = %s\n", data->simple_cmd->cmd);
	// free_pipes(data->pipes, data);
	// free_redir(data->simple_cmd->redirections);
	// if (data->simple_cmd->full_args == NULL)
	// 	;
	// else
	// {
	// 	if (*data->simple_cmd->cmd)
	// 	{
	// 		while (data->simple_cmd->full_args[i])
	// 		{
	// 			printf("arg[i] = %s\n", data->simple_cmd->full_args[i]);
	// 			free(data->simple_cmd->full_args[i++]);
	// 		}
	// 		free(data->simple_cmd->full_args);
	// 	}
	// }
	free(data->simple_cmd->cmd);
	free(data->simple_cmd);
}

void	free_data(t_data *data)
{
	int				i;
	t_list			*tmp;
	t_list			*tmp_cmds;
	t_list			*tmp_pipes;

	if (!data->command->cmds)
		free_last_cmd(data);
	tmp_cmds = data->command->cmds;
	while (tmp_cmds)
	{
		tmp_pipes = tmp_cmds->content;
		free_pipes(tmp_pipes, data);
		tmp = tmp_cmds->next;
		free(tmp_cmds);
		tmp_cmds = tmp;
		// printf("Next command\n");
	}
	i = 0;
	while (data->env[i])
		free(data->env[i++]);
	// printf("freeing env\n");
	free(data->env);
	free(data->command);
}