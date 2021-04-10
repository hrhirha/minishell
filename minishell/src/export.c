/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 15:58:34 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **env, int len)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	display_env_ordred2(char **env, int count)
{
	char	*temp;
	char	**env_temp;
	int		i;
	int		j;

	env_temp = copy_env(env, count);
	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env_temp[i], env_temp[j]) > 0)
			{
				temp = env_temp[i];
				env_temp[i] = env_temp[j];
				env_temp[j] = temp;
			}
			j++;
		}
		i++;
	}
	ex_helper2(env_temp);
	free_double(env_temp);
}

int	display_env_ordred(char **env)
{
	int	count;

	count = words_counter(env);
	display_env_ordred2(env, count);
	return (0);
}

int	shell_export(t_command *command, t_minishell *minishell)
{
	int	i;

	if (command->full_args[1] == NULL)
	{
		display_env_ordred(minishell->env);
		return (1);
	}
	i = 0;
	while (command->full_args[++i] != NULL)
	{
		if (valid_arg_export(command->full_args[i]) == 1)
			export_invalid_arg_msg(command->full_args[i]);
		else if (arg_has_equal(command->full_args[i]) == 1)
		{
			if (export_arg_exist(command->full_args[i], minishell) == 0)
				export_varible_edit(command->full_args[i], minishell);
			else
				export_varible(command->full_args[i], minishell);
		}
		else if (export_arg_exist(command->full_args[i], minishell) == 1)
		{
			export_varible(command->full_args[i], minishell);
		}
	}
	return (1);
}
