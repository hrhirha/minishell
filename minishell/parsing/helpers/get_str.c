/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:24:44 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/09 10:24:45 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*dquoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 1;
	while ((line[*i + j] != '"' || line[*i + j - 1] == '\\') && line[*i + j])
		j++;
	substr = ft_substr(line, *i, j + 1);
	if (line[*i + j] == '"')
		*i += j + 1;
	else
		*i += j;
	return (substr);
}

char	*squoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 1;
	while (line[*i + j] != '\'' && line[*i + j])
		j++;
	substr = ft_substr(line, *i, j + 1);
	if (line[*i + j] == '\'')
		*i += j + 1;
	else
		*i += j;
	return (substr);
}

char	*unquoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 0;
	while ((line[*i + j] != ';' && line[*i + j] != '|' &&
			line[*i + j] != '>' && line[*i + j] != '<' && line[*i + j] &&
			isblank(line[*i + j]) == 1 && line[*i + j] != '"' &&
			line[*i + j] != '\'') || (line[*i + j - 1] == '\\' && line[*i + j]))
		j++;
	substr = ft_substr(line, *i, j);
	*i += j;
	return (substr);
}

char	*get_str(char *line, int *i)
{
	char	*tmp;
	char	*substr;
	char	*str;

	str = ft_calloc(1, 1);
	while (line[*i] != ';' && line[*i] != '|' &&
			line[*i] != '>' && line[*i] != '<' &&
			isblank(line[*i]) == 1 && line[*i])
	{
		if (line[*i] == '"')
			substr = dquoted_str(line, i);
		else if (line[*i] == '\'')
			substr = squoted_str(line, i);
		else
			substr = unquoted_str(line, i);
		tmp = str;
		str = ft_strjoin(str, substr);
		free(tmp);
		free(substr);
	}
	return (str);
}
