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
	while (line[data->i])
	{
		if (line[data->i] == '>' || line[data->i] == '<')
			get_redirection(line, data);
		// data->i++;
	}
}
