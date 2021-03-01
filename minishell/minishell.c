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
			printf("Exec\n");
		free_data(data);
		free(line);
		free(data);
	}
}
