/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:18:39 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/11 17:18:40 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**tabjoin(char **t1, char **t2, int i)
{
	char	**t;
	int		j;
	int		k;

	t = malloc((tab_size(t1) + tab_size(t2)) * sizeof(char *));
	j = -1;
	while (++j < i)
		t[j] = ft_strdup(t1[j]);
	k = 0;
	while (t2[k])
	{
		t[j++] = ft_strdup(t2[k++]);
	}
	while (t1[++i])
	{
		t[j] = ft_strdup(t1[i]);
		j++;
	}
	t[j] = NULL;
	return (t);
}

int	split_arg_exp(int i, t_command *cmd)
{
	int		ret;
	char	**tab_split;
	char	**new_args;
	int		j;

	j = 0;
	while (cmd->full_args[i][j])
	{
		if (cmd->full_args[i][j] == '\t')
			cmd->full_args[i][j] = ' ';
		j++;
	}
	tab_split = ft_split(cmd->full_args[i], ' ');
	ret = tab_size(tab_split);
	new_args = tabjoin(cmd->full_args, tab_split, i);
	free_tab(tab_split);
	free_tab(cmd->full_args);
	cmd->full_args = new_args;
	return (ret);
}
