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

void	test_parsed_line(t_data *data)
{
	t_list			*tmp_cmds;
	t_list			*tmp_pipes;
	t_command		command;
	t_list			*tmp_redir;
	t_redirection	redir;

	tmp_cmds = data->command->cmds;
	while (tmp_cmds)
	{
		int			i = 0;
		tmp_pipes = tmp_cmds->content;
		while (tmp_pipes)
		{
			int j = 0;
			command = *(t_command *)tmp_pipes->content;
			tmp_redir = command.redirections;
			while (tmp_redir)
			{
				printf("redirections\n");
				redir = *(t_redirection *)tmp_redir->content;
				printf("(%d)filename = `%s`\n", redir.type, redir.file_name);
				tmp_redir = tmp_redir->next;
			}
			// if (command.cmd)
				printf("cmd[%d] = `%s`\n", i, command.cmd);
			if (command.full_args)
			{
				while (command.full_args[j])
				{
					printf("arg[%d] = `%s`\n", j, command.full_args[j]);
					j++;
				}
			}
			tmp_pipes = tmp_pipes->next;
			i++;
		}
		tmp_cmds = tmp_cmds->next;
		printf("\n");
	}
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	// data_init(&data);
	// set_env(env, &data);
	while (1)
	{
		data.i = 0;
		write(1, PROMPT, ft_strlen(PROMPT));
		get_next_line(0, &line);
		parse_line(line, &data);
		free(line);

		test_parsed_line(&data);
	}
}
