/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:20:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/13 18:50:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_arg_tab(char *cmd, int acount)
{
	char	**args;
	char	*tmp;
	int		j;
	int		ac;

	args = malloc((acount + 1) * sizeof(char *));
	if (!args)
		exit_errno(ENOMEM);
	ac = 0;
	j = 0;
	while (ac < acount)
	{
		while (isblank(cmd[j]) == 0)
			j++;
		args[ac] = get_str(cmd, &j);
		if (args[ac][ft_strlen(args[ac]) - 1] == ' ')
		{
			tmp = args[ac];
			args[ac] = ft_substr(args[ac], 0, ft_strlen(args[ac]) - 1);
			free(tmp);
		}
		ac++;
	}
	args[ac] = NULL;
	return (args);
}

void	get_command_as_str(char *line, t_data *data)
{
	char	*tmp;
	char	*substr;

	tmp = data->cmd;
	substr = get_str(line, &data->i);
	data->cmd = ft_strjoin(data->cmd, substr);
	free(tmp);
	free(substr);
	tmp = data->cmd;
	data->cmd = ft_strjoin(data->cmd, " ");
	free(tmp);
}

void	get_command_and_args(char *line, t_data *data, int ret)
{
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] != '>' && line[data->i] != '<' &&
		line[data->i] != ';' && line[data->i] != '|' &&
		isblank(line[data->i]) == 1 && line[data->i])
	{
		get_command_as_str(line, data);
		data->ac++;
	}
	if ((line[data->i] == '|' || line[data->i] == ';'
		|| !line[data->i] || ret == 1))
	{
		if (data->ac)
		{
			data->simple_cmd->full_args =
							get_arg_tab(data->cmd, data->ac);
		}
		free(data->cmd);
	}
}
