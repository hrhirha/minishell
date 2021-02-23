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

int		isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}

void	parse_line(char *line, t_data *data)
{
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';')
		exit_error(SNTXERR, line[data->i]);
	if (!(data->simple_cmd = malloc(sizeof(t_command))))
		exit_errno(ENOMEM);
	data->simple_cmd->redirections = NULL;
	while (line[data->i])
	{
		if (line[data->i] == '>' || line[data->i] == '<')
			get_redirection(line, data);
		else if (line[data->i] == '|')
			; // add previous cmd to pipe list
		else if (line[data->i] == ';')
			; // add previous pipe list to command list
		else
			data->i++;
	}
}
