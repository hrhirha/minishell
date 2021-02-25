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



void	parse_line(char *line, t_data *data)
{
	if (!(data->command = malloc(sizeof(t_minishell))))
		exit_errno(ENOMEM);
	data->command->cmds = NULL;
	data->pipes = NULL;
	init_cmd(data);
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';')
		error(SNTXERR, line[data->i]);
	else
	{
		while (line[data->i])
		{
			if (line[data->i] == '>' || line[data->i] == '<')
				get_redirection(line, data);
			else if (line[data->i] == '|')
			{
				// add previous cmd to pipe list
				add_cmd_to_pipes(line, data);
			}
			else if (line[data->i] == ';')
			{
				// add previous cmd to pipe list and 
				// add previous pipe list to command list
				add_pipes_to_cmds(line, data);
			}
			else
			{
				// Get command and arguments
				get_command_and_args(line, data);
				// data->i++;
			}
			if (!line[data->i])
			{
				add_last_cmd(line, data);
			}
		}
	}
}
