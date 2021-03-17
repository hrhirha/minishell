/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:41:39 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/14 18:23:30 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_simple_str(char **str, char *s, int *i, int j)
{
	char	*tmp;
	char	*substr;

	tmp = *str;
	substr = ft_substr(s, *i, j);
	*str = ft_strjoin(*str, substr);
	free(tmp);
	free(substr);
	*i += j;
}

char	*handle_dquotes(char *s, int *i, char **env)
{
	char	*str;
	int		j;

	*i += 1;
	str = ft_calloc(1, 1);
	g_exist.quote = 0;
	while (s[*i] != '"' && s[*i])
	{
		j = 0;
		while (s[*i + j] != '\\' && s[*i + j] != '"'
			&& s[*i + j] != '$' && s[*i + j])
			j++;
		get_simple_str(&str, s, i, j);
		if (s[*i] == '\\')
			handle_escape(s, i, '"', &str);
		else if (s[*i] == '$')
			handle_env_expansion(s	, i, env, &str);
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
	char	*str;
	int		j;

	*i += 1;
	str = ft_calloc(1, 1);
	g_exist.quote = 0;
	j = 0;
	while (s[*i + j] != '\'' && s[*i + j])
		j++;
	get_simple_str(&str, s, i, j);
	if (s[*i] == '\'')
		*i += 1;
	return (str);
}

char	*handle_noquotes(char *s, int *i, char **env)
{
	char	*str;
	int		j;

	str = ft_calloc(1, 1);
	g_exist.quote = 1;
	while (s[*i] != '"' && s[*i] != '\'' && s[*i])
	{
		j = 0;
		while (s[*i + j] != '"' && s[*i + j] != '\'' && s[*i + j] != '\\' &&
				s[*i + j] != '$' && s[*i + j] != '~' && s[*i + j])
			j++;
		get_simple_str(&str, s, i, j);
		if (s[*i] == '\\')
			handle_escape(s, i, '\0', &str);
		else if (s[*i] == '$')
			handle_env_expansion(s, i, env, &str);
		else if (s[*i] == '~')
			handle_tilde_expansion(s, i, env, &str);
	}
	return (str);
}
