/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:53:00 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 16:38:39 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_env(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) != 1 && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	does_env_exist(char *arg, char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (export_env_compair(env[i], arg) == 1)
			return (0);
		i++;
	}
	return (1);
}

void	drop_pro(t_command *cmd, int index)
{
	char	**tb;
	int		i;
	int		j;
	int		len;

	len = index;
	len = tab_size(cmd->full_args);
	tb = (char **)malloc(sizeof(char *) * (len));
	i = 0;
	j = 0;
	while (cmd->full_args[i] != NULL)
	{
		if (i != index)
		{
			tb[j] = ft_strdup(cmd->full_args[i]);
			j++;
		}
		i++;
	}
	tb[j] = NULL;
	free_double(cmd->full_args);
	cmd->full_args = tb;
}
