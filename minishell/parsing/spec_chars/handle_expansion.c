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

void	handle_env_expansion(char *s, int *i, char **env, char **str)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		j;

	*i += 1;
	if (s[*i] == '?')
	{
		value = ft_itoa(g_last_exec);
		*i += 1;
	}
	else
	{
		j = 0;
		while (ft_isalnum(s[*i + j]) == 1 || s[*i + j] == '_')
			j++;
		key = ft_substr(s, *i, j);
		*i += j;
		value = get_env_value(key, env);
		free(key);
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
