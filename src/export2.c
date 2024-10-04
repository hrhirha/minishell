/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 16:46:29 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_invalid_arg_msg(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exist.last_exec = 1;
}

int	valid_arg_export(char *str)
{
	char	**args;
	int		i;

	if (str[0] == '\0')
		return (1);
	if (ft_isdigit(str[0]) == 1)
		return (1);
	args = ft_split(str, '=');
	i = 0;
	while (args[0][i] != '\0')
	{
		if (ft_isalnum(args[0][i]) != 1 && args[0][i] != '_')
		{
			free_double(args);
			return (1);
		}
		i++;
	}
	free_double(args);
	return (0);
}

int	arg_has_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_varible(char *arg, t_minishell *minishell)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *)
			* (words_counter(minishell->env) + 2));
	i = 0;
	while (minishell->env[i] != NULL)
	{
		new_env[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	free_double(minishell->env);
	minishell->env = new_env;
}

char	*env_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (&arg[i + 1]);
		i++;
	}
	return (NULL);
}
