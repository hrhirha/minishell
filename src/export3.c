/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 16:09:57 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_env_compair(char *var1, char *var2)
{
	int		res;
	char	**str1;
	char	**str2;

	if (!var1 && !var2)
		return (0);
	res = 0;
	str1 = ft_split(var1, '=');
	str2 = ft_split(var2, '=');
	if (ft_strcmp(str1[0], str2[0]) == 0)
		res = 1;
	free_double(str1);
	free_double(str2);
	return (res);
}

int	export_arg_exist(char *full_arg, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (export_env_compair(minishell->env[i], full_arg) == 1)
			return (0);
		i++;
	}
	return (1);
}

void	export_varible_edit(char *arg, t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (export_env_compair(minishell->env[i], arg) == 1)
		{
			free(minishell->env[i]);
			minishell->env[i] = ft_strdup(arg);
			return ;
		}
		i++;
	}
}

void	display_env_chars(char *env)
{
	int	len;
	int	i;
	int	first;

	first = 0;
	len = ft_strlen(env);
	i = 0;
	while (i < len)
	{
		if ((env[i] == 61) && (first == 0))
		{
			ft_putchar_fd(env[i], 1);
			ft_putchar_fd('"', 1);
			first = 1;
		}
		else
		{
			if (env[i] == 36 || env[i] == 39 || env[i] == 34)
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(env[i], 1);
		}
		i++;
	}
	if (first == 1)
		ft_putchar_fd('"', 1);
}

void	ex_helper2(char **env)
{
	int	j;

	j = 0;
	while (env[j] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		display_env_chars(env[j]);
		ft_putchar_fd('\n', 1);
		j++;
	}
}
