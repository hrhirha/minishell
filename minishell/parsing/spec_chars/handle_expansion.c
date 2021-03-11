/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:51:06 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/03 10:51:09 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char *key, char **env)
{
	char	*env_key;
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	env_value = ft_calloc(1, 1);
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		env_key = ft_substr(env[i], 0, j);
		if (ft_strcmp(key, env_key) == 0)
			break ;
		free(env_key);
		i++;
	}
	if (env[i])
	{
		free(env_value);
		env_value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
		free(env_key);
	}
	return (env_value);
}

void	ambigious_redirect(char *key, char **value, char *str)
{
	if (ft_strchr(*value, ' ') || ft_strchr(*value, '\t') || **value == '\0')
	{
		if (*str == '\0')
			printf("$%s is ambigious redirect\n", key);
		free(*value);
		*value = ft_strdup("");
	}
}

void	handle_env_expansion(char *s, int *i, char **env, char **str)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		j;

	*i += 1;
	j = 0;
	while (ft_isalnum(s[*i + j]) == 1 || s[*i + j] == '_')
		j++;
	key = ft_substr(s, *i, j);
	*i += j;
	value = get_env_value(key, env);
	if (t_exist.dir && t_exist.quote)
	{
		ambigious_redirect(key, &value, *str);
	}
	free(key);
	tmp = *str;
	*str = ft_strjoin(*str, value);
	free(tmp);
	free(value);
}

void	handle_tilde_expansion(char *s, int *i, char **env, char **str)
{
	char	*tmp;
	char	*tilde;

	if (isblank(s[*i + 1]) == 0 || s[*i + 1] == '/' || !s[*i + 1])
	{
		tilde = get_env_value("HOME", env);
		tmp = *str;
		*str = ft_strjoin(*str, tilde);
		free(tilde);
		free(tmp);
	}
	else
	{
		tmp = *str;
		*str = ft_strjoin(*str, "~");
		free(tmp);
	}
	*i += 1;
}
