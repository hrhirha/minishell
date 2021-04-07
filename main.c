/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 16:28:13 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gnl_term(char **line);

void	ft_getline(char **line, t_data *data)
{
	int parsing_ret;

	data->i = 0;
	write(1, PROMPT, ft_strlen(PROMPT));
	// get_next_line(0, line);
	tcgetattr(0, &g_exist.tc.init);
	gnl_term(line);
	tcsetattr(0, TCSANOW, &g_exist.tc.init);
	parsing_ret = parse_line(*line, data);
	if (parsing_ret == 0)
		pipes_loop(data->command);
	free_data(data);
}

void	init_data(t_data *data, char **env)
{
	data->command = malloc(sizeof(t_minishell));
	if (!data->command)
		exit_errno(ENOMEM);
	set_env(env, data);
	data->command->out = dup(1);
	data->command->in = dup(0);
	g_exist.hist = NULL;
}

void	free_hist()
{
	t_hist *h;
	t_hist *tmp;
	
	h = g_exist.hist;
	while (h)
	{
		printf("`%s`\n", h->s);
		free(h->s);
		tmp = h->next;
		h = tmp;
	}
	free(h);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		exit_errno(ENOMEM);
	init_data(data, env);
	while (1)
	{
		line = NULL;
		g_exist.pid = 0;
		ft_getline(&line, data);
		free(line);
	}
	free_tab(data->command->env);
	free(data->command);
	free_hist();
	free(data);
}
