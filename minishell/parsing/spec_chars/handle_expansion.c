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

void	env_val_has_blanks(char *s, int *i, char *value, char **str)
{
	if (ft_strchr(value, ' ') || ft_strchr(value, '\t'))
	{
		while (s[*i])
			*i += 1;
		free(*str);
		*str = ft_strdup("");
	}
}

char	*env_variable(char *s, int *i, char **env, char **str)
{
	int		j;
	char	*key;
	char	*value;

	j = 0;
	while (ft_isalnum(s[*i + j]) == 1 || s[*i + j] == '_')
		j++;
	key = ft_substr(s, *i, j);
	*i += j;
	value = get_env_value(key, env);
	if (t_exist.dir && t_exist.quote)
	{
		if (ft_strchr(value, ' ') || ft_strchr(value, '\t') || *value == '\0')
		{
			env_val_has_blanks(s, i, value, str);
			if (**str == '\0')
				ft_putstr_fd("ambiguous redirect\n", 2);
			free(value);
			value = ft_strdup("");
		}
	}
	free(key);
	return (value);
}

void	handle_env_expansion(char *s, int *i, char **env, char **str)
{
	char	*value;
	char	*tmp;

	*i += 1;
	if (s[*i] == '?')
	{
		value = ft_itoa(g_last_exec);
		*i += 1;
	}
	else
	{
		value = env_variable(s, i, env, str);
	}
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
