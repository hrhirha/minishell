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

#include "../../minishell.h"

void	update_env_shlvl(t_data *data)
{
	char	*tmp;
	char	*shlvl;
	int		lvl;

	tmp = get_env_value("SHLVL", data->command->env);
	lvl = ft_atoi(tmp);
	lvl++;
	free(tmp);
	tmp = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", tmp);
	if (export_arg_exist(shlvl, data->command) == 0)
		export_varible_edit(shlvl, data->command);
	else
		export_varible(shlvl, data->command);
	free(tmp);
	free(shlvl);
}

void	set_env(char **s, t_data *data)
{
	int	x;
	int	i;

	x = 0;
	while (s[x])
		x++;
	data->command->env = malloc((x + 1) * sizeof(char *));
	if (!data->command->env)
		exit_errno(ENOMEM);
	i = 0;
	while (i < x)
	{
		data->command->env[i] = ft_strdup(s[i]);
		i++;
	}
	data->command->env[i] = NULL;
	update_env_pwd(data);
	update_env_shlvl(data);
}

int		search_env(char *key, char **env, int i, int *j)
{
	char *env_key;

	*j = 0;
	while (env[i][*j] != '=' && env[i][*j])
		*j += 1;
	env_key = ft_substr(env[i], 0, *j);
	if (ft_strcmp(key, env_key) == 0)
	{
		free(env_key);
		return (0);
	}
	free(env_key);
	return (1);
}

char	*get_env_value(char *key, char **env)
{
	char	*tmp;
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	env_value = ft_calloc(1, 1);
	while (env[i])
	{
		if (search_env(key, env, i, &j) == 0)
			break ;
		i++;
	}
	if (env[i])
	{
		free(env_value);
		env_value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	}
	if (g_exist.quote)
	{
		tmp = env_value;
		env_value = ft_strtrim(env_value, "\t ");
		free(tmp);
	}
	return (env_value);
}

void	export_env_var(char *arg, t_minishell *minishell)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) *
		(words_counter(minishell->env) + 2));
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

void	set_pwd_oldpwd(char *new_path, t_minishell *minishell, int type)
{
	int		pwd;
	int		oldpwd;
	int		j;
	char	*tmp;
	char	*tmp1;

	oldpwd = -1;
	while (minishell->env[++oldpwd])
	{
		if (search_env("OLDPWD", minishell->env, oldpwd, &j) == 0)
			break ;
	}
	pwd = 0;
	while (minishell->env[pwd])
	{
		if (search_env("PWD", minishell->env, pwd, &j) == 0)
			break ;
		pwd++;
	}
	if (!minishell->env[pwd])
	{
		export_env_var(ft_strjoin("PWD=", new_path), minishell);
	}
	else
	{
		tmp = ft_strjoin("OLDPWD=", get_env_value("PWD", minishell->env));
		if (!minishell->env[oldpwd] && minishell->env[pwd])
			export_env_var(tmp, minishell);
		else if (minishell->env[oldpwd] && minishell->env[pwd])
			update_env_var(tmp, minishell);
		free(tmp);
		tmp = ft_strjoin(&minishell->env[oldpwd][7], "/.");
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
}
