/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:23:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/20 15:45:52 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <signal.h>

static	void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

static	int		ft_line_found(char *s)
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

static	int		ft_read_file(int fd, char **storage)
{
	char	*buf;
	char	*tmp;
	int		rd;

	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (ft_line_found(*storage) == -1)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1 || rd == 0)
			break ;
		buf[rd] = '\0';
		tmp = *storage;
		*storage = ft_strjoin(*storage, buf);
		ft_free(&tmp);
	}
	ft_free(&buf);
	return (rd);
}

static	char	*ft_fill_line(char *s)
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

int				get_next_line(int fd, char **line)
{
	static char *storage;
	char		*tmp;
	int			rd;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 0)
		return (-1);
	if (!storage && !(storage = ft_calloc(1, 1)))
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	if (ft_line_found(storage) == -1)
	{
		rd = ft_read_file(fd, &storage);
		if (rd == -1)
			return (rd);
		else if (rd == 0)
		{
			*line = ft_strdup(storage);
			ft_free(&storage);
			return (0);
		}
	}
	*line = ft_fill_line(storage);
	tmp = storage;
	storage = ft_strdup(storage + ft_line_found(storage) + 1);
	ft_free(&tmp);
	return (1);
}
