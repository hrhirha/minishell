/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:53:00 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/05 18:39:19 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}

void	init_cmd(t_data *data)
{
	if (!(data->simple_cmd = malloc(sizeof(t_command))))
		exit_errno(ENOMEM);
	if (!(data->cmd = ft_calloc(1, 1)))
		exit_errno(ENOMEM);
	data->simple_cmd->redirections = NULL;
	data->simple_cmd->full_args = NULL;
	data->ac = 0;
}
