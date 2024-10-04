/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 15:40:14 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (ft_strchr(minishell->env[i], '=') != NULL)
		{
			ft_putstr_fd(minishell->env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	g_exist.last_exec = 0;
	return (1);
}
