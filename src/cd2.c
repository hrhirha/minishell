/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:09:53 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 16:56:15 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_env_var(char *arg, t_minishell *minishell)
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

void	update_env_var(char *arg, t_minishell *minishell)
{
	int		i;
	char	**new;

	new = malloc((tab_size(minishell->env) + 1) * sizeof(char *));
	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (export_env_compair(minishell->env[i], arg) == 1)
		{
			new[i] = ft_strdup(arg);
		}
		else
			new[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	new[i] = NULL;
	free_tab(minishell->env);
	minishell->env = new;
}

void	set_pwd_oldpwd2(char *new_path, t_minishell *minishell,
		int type, int *pwd_arr)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = get_env_value("PWD", minishell->env);
	tmp = ft_strjoin("OLDPWD=", tmp1);
	free(tmp1);
	if (!minishell->env[pwd_arr[1]] && minishell->env[pwd_arr[0]])
		export_env_var(tmp, minishell);
	else if (minishell->env[pwd_arr[1]] && minishell->env[pwd_arr[0]])
		update_env_var(tmp, minishell);
	free(tmp);
	tmp = ft_strjoin(&minishell->env[pwd_arr[1]][7], "/.");
	if (type == 1)
	{
		tmp1 = ft_strjoin("PWD=", new_path);
		update_env_var(tmp1, minishell);
		free(tmp1);
	}
	else
	{
		tmp1 = ft_strjoin("PWD=", tmp);
		update_env_var(tmp, minishell);
		free(tmp1);
	}
	free(tmp);
}

void	set_pwd_oldpwd(char *new_path, t_minishell *minishell, int type)
{
	int		j;
	char	*tmp;
	int		pwd_arr[2];

	pwd_arr[1] = -1;
	while (minishell->env[++pwd_arr[1]])
	{
		if (search_env("OLDPWD", minishell->env, pwd_arr[1], &j) == 0)
			break ;
	}
	pwd_arr[0] = 0;
	while (minishell->env[pwd_arr[0]])
	{
		if (search_env("PWD", minishell->env, pwd_arr[0], &j) == 0)
			break ;
		pwd_arr[0]++;
	}
	if (!minishell->env[pwd_arr[0]])
	{
		tmp = ft_strjoin("PWD=", new_path);
		export_env_var(tmp, minishell);
		free(tmp);
	}
	else
		set_pwd_oldpwd2(new_path, minishell, type, pwd_arr);
}
