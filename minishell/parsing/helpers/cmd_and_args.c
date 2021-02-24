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

void	get_command_and_args(char *line, t_data *data)
{
	int		j;
	int		ac;
	char	*substr;

	while (isblank(line[data->i]) == 0)
		data->i++;
	substr = get_str(line, &data->i);
	data->simple_cmd->cmd = ft_strjoin(data->simple_cmd->cmd, substr);
	data->simple_cmd->cmd = ft_strjoin(data->simple_cmd->cmd, " ");
	data->ac++;
	if (line[data->i] == '|' || line[data->i] == ';' || line[data->i])
	{
		if (!(data->simple_cmd->full_args =
								malloc(data->ac * sizeof(char *) + 1)))
			exit_errno(ENOMEM);
		ac = 0;
		j = 0;
		while (ac < data->ac)
		{
			data->simple_cmd->full_args[ac] =
								get_str(data->simple_cmd->cmd, &j);
			// j++;
			ac++;
		}
		data->simple_cmd->full_args[ac] = NULL;
	}
}
