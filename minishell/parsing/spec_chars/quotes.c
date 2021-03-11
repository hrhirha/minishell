/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:41:39 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/02 12:41:41 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_dquotes(char *s, int *i, char **env)
{
	char	*tmp;
	char	*str;
	char	*substr;
	int		j;

	*i += 1;
	str = ft_calloc(1, 1);
	t_exist.quote = 0;
	while (s[*i] != '"' && s[*i])
	{
		j = 0;
		while (s[*i + j] != '\\' && s[*i + j] != '"'
			&& s[*i + j] != '$' && s[*i + j])
			j++;
		tmp = str;
		substr = ft_substr(s, *i, j);
		str = ft_strjoin(str, substr);
		free(tmp);
		free(substr);
		*i += j;
		if (s[*i] == '\\')
		{
			// TODO: handle escape char
			handle_escape(s, i, '"', &str);
		}
		else if (s[*i] == '$')
		{
			// TODO: handle env expansion($)
			// can only be followed by alnum values or _
			handle_env_expansion(s	, i, env, &str);
		}
		if (s[*i] == '"')
		{
			*i += 1;
			break ;
		}
	}
	return (str);
}

char	*handle_squotes(char *s, int *i)
{
	char	*tmp;
	char	*str;
	char	*substr;
	int	 j;

	*i += 1;
	str = ft_calloc(1, 1);
	j = 0;
	while (s[*i + j] != '\'' && s[*i + j])
		j++;
	tmp = str;
	substr = ft_substr(s, *i, j);
	str = ft_strjoin(str, substr);
	free(tmp);
	free(substr);
	*i += j;
	if (s[*i] == '\'')
		*i += 1;
	return (str);
}

char	*handle_noquotes(char *s, int *i, char **env)
{
	char	*tmp;
	char	*str;
	char	*substr;
	int	 j;

	t_exist.quote = 1;
	str = ft_calloc(1, 1);
	while (s[*i] != '"' && s[*i] != '\'' && s[*i])
	{
		j = 0;
		while (s[*i + j] != '"' && s[*i + j] != '\'' &&s[*i + j] != '\\' &&
				s[*i + j] != '$' && s[*i + j] != '~' && s[*i + j])
				j++;
		tmp = str;
		substr = ft_substr(s, *i, j);
		str = ft_strjoin(str, substr);
		free(tmp);
		free(substr);
		*i += j;
		if (s[*i] == '\\')
		{
			// TODO: handle escape char
			handle_escape(s, i, '\0', &str);
		}
		else if (s[*i] == '$')
		{
			// TODO: handle env expansion($)
			// can only be followed by alnum values or _
			handle_env_expansion(s, i, env, &str);
		}
		else if (s[*i] == '~')
		{
			// only works if followed by a blank or /, or a username
			handle_tilde_expansion(s, i, env, &str);
		}
	}
	return (str);
}
