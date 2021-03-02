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

void	handle_dquotes(char *s, int *i)
{
	char	*tmp;
	char	*quoted_str;
	char	*substr;
	int	 j;

	*i++;
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
			substr = handle_escape(s, data);
			quoted_str = ft_strjoin(quoted_str, substr);
			*i++;
		}
		else if (s[*i] == '$')
		{
			// TODO: handle expansion
		}
	}
	return (quoted_str);
}
