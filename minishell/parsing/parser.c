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

void	init_cmd(t_data *data)
{
	if (!(data->simple_cmd = malloc(sizeof(t_command))))
		exit_errno(ENOMEM);
	if (!(data->simple_cmd->cmd = ft_calloc(1, 1)))
		exit_errno(ENOMEM);
	data->simple_cmd->redirections = NULL;
	data->ac = 0;
}

void	parse_line(char *line, t_data *data)
{
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';')
		exit_error(SNTXERR, line[data->i]);
	if (!(data->command = malloc(sizeof(t_minishell))))
		exit_errno(ENOMEM);
	init_cmd(data);
	data->pipes = NULL;
	data->command->cmds = NULL;
	while (line[data->i])
	{
		if (line[data->i] == '>' || line[data->i] == '<')
			get_redirection(line, data);
		else if (line[data->i] == '|')
		{
			// add previous cmd to pipe list
			ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
			init_cmd(data);
			data->i++;
			while (isblank(line[data->i]) == 0)
				data->i++;
		}
		else if (line[data->i] == ';')
		{
			// add previous cmd to pipe list and 
			// add previous pipe list to command list
			data->i++;
		}
		else
		{
			// Get command and arguments
			get_command_and_args(line, data);
			// data->i++;
		}
		if (!line[data->i])
			ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
	}
}
