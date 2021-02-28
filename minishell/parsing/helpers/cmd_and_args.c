/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:20:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/24 11:20:15 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_arg_tab(char *cmd, int acount)
{
	char	**args;
	int		j;
	int		ac;

	if (!(args = malloc((acount + 1) * sizeof(char *))))
		exit_errno(ENOMEM);
	ac = 0;
	j = 0;
	while (ac < acount)
	{
		args[ac] = get_str(cmd, &j);
		while (isblank(cmd[j]) == 0)
			j++;
		ac++;
	}
	args[ac] = NULL;
	return (args);
}

void	get_command_and_args(char *line, t_data *data)
{
	char	*tmp;
	char	*substr;

	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] != '>' && line[data->i] != '<' &&
		line[data->i] != ';' && line[data->i] != '|' &&
		line[data->i] != ' ' && line[data->i])
	{
		tmp = data->simple_cmd->cmd;
		substr = get_str(line, &data->i);
		data->simple_cmd->cmd = ft_strjoin(data->simple_cmd->cmd, substr);
		free(tmp);
		free(substr);
		tmp = data->simple_cmd->cmd;
		data->simple_cmd->cmd = ft_strjoin(data->simple_cmd->cmd, " ");
		free(tmp);
		data->ac++;
	}
	if (line[data->i] == '|' || line[data->i] == ';' || !line[data->i])
	{	
		data->simple_cmd->full_args =
						get_arg_tab(data->simple_cmd->cmd, data->ac);
	}
}
