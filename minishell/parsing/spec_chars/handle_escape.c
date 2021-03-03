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

char	*handle_escape(char *s, int *i, char c)
{
	char *sub;

	if ((s[*i + 1] == '$' || s[*i + 1] == '"' || s[*i + 1] == '\\') && c == '"')
		sub = ft_substr(s, *i + 1, 1);
	else
		sub = ft_substr(s, *i, 2);
	*i += 2;
	return (sub);
}
