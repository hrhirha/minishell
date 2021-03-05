/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:41:56 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/02 12:41:59 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** escape char '\' if present within double quotes,
** only skipped if followed by `$` `"` `\`.
** but it is always skipped withen unquoted string
*/

void	handle_escape(char *s, int *i, char c, char **str)
{
	char	*sub;
	char	*tmp;

	if (s[*i + 1] != '$' && s[*i + 1] != '"' && s[*i + 1] != '\\' && c == '"')
		sub = ft_substr(s, *i, 2);
	else
		sub = ft_substr(s, *i + 1, 1);
	*i += 2;
	tmp = *str;
	*str = ft_strjoin(*str, sub);
	free(tmp);
	free(sub);
}
