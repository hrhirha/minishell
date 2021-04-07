/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 15:47:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		valid_arg(char *str)
{
	int i;

	if (ft_isdigit(str[0]) == 1)
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) != 1 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int		env_compair(char *var1, char *arg)
{
	int		res;
	char	**str1;

	res = 0;
	str1 = ft_split(var1, '=');
	if (ft_strcmp(str1[0], arg) == 0)
		res = 1;
	free_double(str1);
	return (res);
}

int		arg_exist(char *arg, t_minishell *minishell)
{
	int i;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (env_compair(minishell->env[i], arg) == 1)
			return (0);
		i++;
	}
	return (1);
}

void	unset_varible(char *arg, t_minishell *minishell)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) *
		(words_counter(minishell->env) + arg_exist(arg, minishell)));
	i = 0;
	j = 0;
	while (minishell->env[i] != NULL)
	{
		if (env_compair(minishell->env[i], arg) == 0)
		{
			new_env[j] = ft_strdup(minishell->env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_double(minishell->env);
	minishell->env = new_env;
}

int		shell_unset(t_command *command, t_minishell *minishell)
{
	int i;

	i = 1;
	while (command->full_args[i] != NULL)
	{
		if (valid_arg(command->full_args[i]) == 1)
			unset_invalid_arg_msg(command->full_args[i]);
		else
			unset_varible(command->full_args[i], minishell);
		i++;
	}
	return (1);
}
