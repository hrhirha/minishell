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

void	data_init(t_data *data)
{
	data->i = 0;
	data->command->cmds = NULL;
	data->pipes = NULL;
	data->redirections = NULL;
	if (!(data->command = malloc(sizeof(t_minishell *))))
		exit_errno(ENOMEM);
	// if (!(data->pipeline = malloc(sizeof(t_pipeline *))))
		// exit_errno(ENOMEM);
	if (!(data->simple_cmd = malloc(sizeof(t_command *))))
		exit_errno(ENOMEM);
	
}

void	set_env(char **s, t_data *data)
{
	int x;

	x = 0;
	while (s[x])
		x++;
	if (!(data->env = malloc(x * sizeof(char *) + 1)))
		exit_errno(ENOMEM);
	data->env[x] = NULL;
	while (--x >= 0)
		data->env[x] = ft_strdup(s[x]);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	data_init(&data);
	// set_env(env, &data);
	while (1)
	{
		data.i = 0;
		write(1, PROMPT, ft_strlen(PROMPT));
		get_next_line(0, &line);
		parse_line(line, &data);
		free(line);
	}
}
