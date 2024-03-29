/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:37:55 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/20 17:46:06 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	line_loop(char *line, t_data *data)
{
	int	ret;

	ret = 0;
	if (!line[data->i])
		ret = 1;
	while (line[data->i])
	{
		if (line[data->i] == '>' || line[data->i] == '<')
			ret = get_redirection(line, data);
		else if (line[data->i] == '|')
		{
			ret = add_cmd_to_pipes(line, data);
		}
		else if (line[data->i] == ';')
		{
			ret = add_pipes_to_cmds(line, data);
		}
		else
			get_command_and_args(line, data, ret);
		if (!line[data->i] || ret == 1)
		{
			add_last_cmd(line, data);
			break ;
		}
	}
	return (ret);
}

int	parse_line(char *line, t_data *data)
{
	int	ret;

	ret = 0;
	data->redirection = NULL;
	data->command->cmds = NULL;
	data->pipes = NULL;
	init_cmd(data);
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';')
		ret = error(SNTXERR, line[data->i]);
	else
	{
		ret = line_loop(line, data);
	}
	return (ret);
}
