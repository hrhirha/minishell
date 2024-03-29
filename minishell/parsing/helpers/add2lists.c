/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add2lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:39:06 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/05 18:39:07 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_cmd_to_pipes(char *line, t_data *data)
{
	int		ret;

	ret = 0;
	data->i++;
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';' || line[data->i] == '\0')
		ret = error(SNTXERR, line[data->i]);
	if (ret == 0)
	{
		ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
		init_cmd(data);
	}
	return (ret);
}

int	add_pipes_to_cmds(char *line, t_data *data)
{
	int		ret;

	ret = 0;
	data->i++;
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';')
		ret = error(SNTXERR, line[data->i]);
	ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
	ft_lstadd_back(&data->command->cmds, ft_lstnew(data->pipes));
	if (line[data->i] && line[data->i] != '|' && line[data->i] != ';')
	{
		data->pipes = NULL;
		init_cmd(data);
	}
	return (ret);
}

void	add_last_cmd(char *line, t_data *data)
{
	data->i--;
	while (isblank(line[data->i]) == 0)
		data->i--;
	if (line[data->i] != ';' || line[data->i - 1] == '\\')
	{
		ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
		ft_lstadd_back(&data->command->cmds, ft_lstnew(data->pipes));
	}
	data->i++;
	while (isblank(line[data->i]) == 0)
		data->i++;
}
