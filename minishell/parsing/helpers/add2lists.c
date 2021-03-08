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

int		pipes_miltilines(char **curr_line, t_data *data)
{
	int		ret;
	char	*tmp;

	ret = 0;
	tmp = *curr_line;
	while (!tmp[data->i])
	{
		write (1, "> ", 2);
		data->i = 0;
		tmp = *curr_line;
		get_next_line(0, curr_line);
		free(tmp);
		tmp = *curr_line;
		while (isblank(tmp[data->i]) == 0)
			data->i++;
		if (tmp[data->i] == '|' || tmp[data->i] == ';')
			ret = error(SNTXERR, tmp[data->i]);
	}
	return (ret);
}

int		add_cmd_to_pipes(char **curr_line, t_data *data)
{
	int		ret;
	char	*line;

	line = *curr_line;
	ret = 0;
	data->i++;
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';')
		ret = error(SNTXERR, line[data->i]);
	else if (line[data->i] == '\0')
	{
		ret = pipes_miltilines(curr_line, data);
	}
	if (ret == 0)
	{
		ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
		init_cmd(data);
	}
	return (ret);
}

int		add_pipes_to_cmds(char *line, t_data *data)
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
	(void)line;
	data->i--;
	while (isblank(line[data->i]) == 0)
		data->i--;
	if (line[data->i] != ';')
	{
		ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
		ft_lstadd_back(&data->command->cmds, ft_lstnew(data->pipes));
	}
	data->i++;
	while (isblank(line[data->i]) == 0)
		data->i++;
}
