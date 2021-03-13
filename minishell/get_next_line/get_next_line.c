/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:23:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/06 15:46:59 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static		int	ft_read_file(int fd, char **storage)
{
	char	*buf;
	char	*tmp;
	int		rd;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
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

void			ctrld(char *storage)
{
	if (*storage == '\0')
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
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
	if (ft_line_found(storage) == -1)
	{
		rd = ft_read_file(fd, &storage);
		if (rd == -1)
			return (rd);
		else if (rd == 0)
		{
			ctrld(storage);
			get_next_line(fd, line);
			return (0);
		}
	}
	*line = ft_fill_line(storage);
	tmp = storage;
	storage = ft_strdup(storage + ft_line_found(storage) + 1);
	ft_free(&tmp);
	return (1);
}
