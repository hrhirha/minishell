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
	char	*quoted_str;
	char	*substr;
	int	 j;

	*i += 1;
	quoted_str = ft_calloc(1, 1);
	while (s[*i] != '"' && s[*i])
	{
		j = 0;
		while (s[*i + j] != '\\' && s[*i + j] != '"' &&
				s[*i + j] != '$' && s[*i + j])
				j++;
		tmp = quoted_str;
		substr = ft_substr(s, *i, j);
		quoted_str = ft_strjoin(quoted_str, substr);
		free(tmp);
		free(substr);
		*i += j;
		if (s[*i] == '\\')
		{
			// TODO: handle escape char
			tmp = quoted_str;
			substr = handle_escape(s, i, '"');
			quoted_str = ft_strjoin(quoted_str, substr);
			free(tmp);
			free(substr);
		}
		else if (s[*i] == '$')
		{
			// TODO: handle env expansion($)
			// can only be followed by alnum values or _
			tmp = quoted_str;
			substr = handle_env_expansion(s	, i, env);
			quoted_str = ft_strjoin(quoted_str, substr);
			free(tmp);
			free(substr);
		}
		if (s[*i] == '"')
			*i += 1;
	}
	return (quoted_str);
}
