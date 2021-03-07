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

void	set_env(char **s, t_data *data)
{
	int x;
	int	i;

	x = 0;
	while (s[x])
		x++;
	data->env = malloc((x + 1) * sizeof(char *));
	if (!data->env)
		exit_errno(ENOMEM);
	i = 0;
	while (i < x)
	{
		data->env[i] = ft_strdup(s[i]);
		i++;
	}
	data->env[i] = NULL;
}

void	exec_command(t_command *command)
{
	t_list			*redirs;
	t_redirection	redir;
	int				j;

	redirs = command->redirections;
	while (redirs)
	{
		redir = *(t_redirection *)redirs->content;
		printf("[%d]file = `%s`\n", redir.type, redir.file_name);
		redirs = redirs->next;
	}
	if (command->full_args)
	{
		j = 0;
		while (command->full_args[j])
		{
			printf("\targ[%d] = `%s`\n", j, command->full_args[j]);
			j++;
		}
	}
}

void	test(t_minishell *command)
{
	t_list		*cmds;
	t_list		*pipes;
	t_command	*cmd;

	cmds = command->cmds;
	while (cmds)
	{
		pipes = cmds->content;
		scan_command(pipes, command->env);
		while (pipes)
		{
			cmd = (t_command *)pipes->content;
			exec_command(cmd);
			pipes = pipes->next;
		}
		cmds = cmds->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;
	int		parsing_ret;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			exit_errno(ENOMEM);
		set_env(env, data);
		data->i = 0;
		write(1, PROMPT, ft_strlen(PROMPT));
		get_next_line(0, &line);
		parsing_ret = parse_line(&line, data);
		if (parsing_ret == 0)
			test(data->command);
		free_data(data);
		free(line);
		free(data);
	}
}
