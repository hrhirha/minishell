/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:23:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/16 18:29:57 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../minishell.h"

static	void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_free(&g_exist.storage);
		if (g_exist.pid == 0)
		{
			ft_putstr_fd("\n", 1);
			write(1, PROMPT, ft_strlen(PROMPT));
		}
		else if (g_exist.pid == 1)
			ft_putstr_fd("\n", 1);
	}
	if (sig == SIGQUIT)
	{
		if (g_exist.pid == 1)
			ft_putstr_fd("Quit:\n", 1);
	}
}

static		int	ft_read_file(int fd, char **storage)
{
	char	*buf;
	char	*tmp;
	int		rd;

	signal(SIGINT, signals);
	signal(SIGQUIT, signals);
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

static	void	ctrld(char *storage)
{
	if (!storage || *storage == '\0')
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

int				get_next_line(int fd, char **line)
{
	char		*tmp;
	int			rd;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 0)
		return (-1);
	if (!g_exist.storage && !(g_exist.storage = ft_calloc(1, 1)))
		return (-1);
	if (ft_line_found(g_exist.storage) == -1)
	{
		rd = ft_read_file(fd, &g_exist.storage);
		if (rd == -1)
			return (rd);
		else if (rd == 0)
		{
			ctrld(g_exist.storage);
			get_next_line(fd, line);
			return (0);
		}
	}
	*line = ft_fill_line(g_exist.storage);
	tmp = g_exist.storage;
	g_exist.storage = ft_strdup(g_exist.storage
					+ ft_line_found(g_exist.storage) + 1);
	ft_free(&tmp);
	return (1);
}
