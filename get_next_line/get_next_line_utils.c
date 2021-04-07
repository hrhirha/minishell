/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:22:49 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/19 10:11:03 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

int		ft_line_found(char *s)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s++ == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_fill_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!(line = malloc(ft_line_found(s) + 1)))
		return (NULL);
	while (s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
