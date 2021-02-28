/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/20 17:46:08 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PROMPT "user@minishell$ "

// void	data_init(t_data *data)
// {
// 	// data->i = 0;
// 	// data->ac = 0;
// 	// data->command = NULL; // struct containing list of commands and $ENV
// 	// data->command->env = NULL; // $ENV
// 	// data->command->cmds = NULL; // listof commands
// 	// data->pipes = NULL; // list of pipes
// 	// data->simple_cmd = NULL;
// 	// data->simple_cmd->redirections = NULL; // list of redirections
// 	// data->redirection = NULL;
// }

// void	set_env(char **s, t_data *data)
// {
// 	int x;

// 	x = 0;
// 	while (s[x])
// 		x++;
// 	if (!(data->env = malloc(x * sizeof(char *) + 1)))
// 		exit_errno(ENOMEM);
// 	data->env[x] = NULL;
// 	while (--x >= 0)
// 		data->env[x] = ft_strdup(s[x]);
// }

void	free_redir(t_list *redirs)
{
	t_list			*tmp;
	t_redirection	redir;

	while (redirs)
	{
		redir = *(t_redirection *)redirs->content;
		free(redir.file_name);
		tmp = redirs->next;
		free(redirs->content);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmd(t_command *command)
{
	int				j;
	t_list			*tmp_redir;

	j = 0;
	tmp_redir = command->redirections;
	free_redir(tmp_redir);
	if (*command->cmd)
	{
		if (command->full_args == NULL)
			;
		else
		{
			while (command->full_args[j])
				free(command->full_args[j++]);
			free(command->full_args);
		}
	}
	free(command->cmd);
}

void	free_pipes(t_list *pipes)
{
	t_command		command;
	t_list			*tmp;

	while (pipes)
	{
		command = *(t_command *)pipes->content;
		free_cmd(&command);
		tmp = pipes->next;
		free(pipes->content);
		free(pipes);
		pipes = tmp;
	}
}

void	free_data(t_data *data)
{
	t_list			*tmp;
	t_list			*tmp_cmds;
	t_list			*tmp_pipes;
	int i = 0;

	if (!data->command->cmds)
	{
		printf("freeing data\n");
		printf("cmd = %s\n", data->simple_cmd->cmd);
		free_pipes(data->pipes);
		free_redir(data->simple_cmd->redirections);
		if (data->simple_cmd->full_args == NULL)
		;
		else
		{
			if (*data->simple_cmd->cmd)
			{
				while (data->simple_cmd->full_args[i])
				{
					printf("arg[i] = %s\n", data->simple_cmd->full_args[i]);
					free(data->simple_cmd->full_args[i++]);
				}
				free(data->simple_cmd->full_args);
			}
		}
		free(data->simple_cmd->cmd);
		free(data->simple_cmd);
	}
	tmp_cmds = data->command->cmds;
	while (tmp_cmds)
	{
		tmp_pipes = tmp_cmds->content;
		free_pipes(tmp_pipes);
		tmp = tmp_cmds->next;
		free(tmp_cmds);
		tmp_cmds = tmp;
	}
	free(data->command);
}

int		main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;
	int		parsing_ret;

	(void)ac;
	(void)av;
	(void)env;
	// set_env(env, &data);
	while (1)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			exit_errno(ENOMEM);
		data->i = 0;
		write(1, PROMPT, ft_strlen(PROMPT));
		get_next_line(0, &line);
		parsing_ret = parse_line(line, data);
		printf("parison_ret = %d\n", parsing_ret);
		if (parsing_ret == 0)
		;
		free(line);
		free_data(data);
		free(data);
	}
}
