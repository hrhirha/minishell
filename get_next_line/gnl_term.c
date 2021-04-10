/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:14:31 by hrhirha           #+#    #+#             */
/*   Updated: 2021/04/09 11:14:32 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_term.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_free(&g_exist.line);
		if (g_exist.tmp_line)
			ft_free(&g_exist.tmp_line);
		g_exist.tmp_hist = NULL;
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

void	setup_term(void)
{
	g_exist.tc.name = getenv("TERM");
	// if (!g_exist.tc.name)
	// 	printf("TERM environment variable not set.\n");
	tgetent(NULL, g_exist.tc.name);
	setupterm(g_exist.tc.name, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_exist.tc.term);
	g_exist.tc.term.c_lflag = g_exist.tc.term.c_lflag & ~ICANON;
	g_exist.tc.term.c_lflag = g_exist.tc.term.c_lflag & ~ECHO;
	g_exist.tc.term.c_cc[VMIN] = 1;
	g_exist.tc.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_exist.tc.term);
}

void	get_printable(long c)
{
	char	bf[2];
	char	*tmp;

	bf[0] = c;
	bf[1] = '\0';
	if (g_exist.line)
	{
		tmp = g_exist.line;
		g_exist.line = ft_strjoin(g_exist.line, bf);
		free(tmp);
	}
	else
		g_exist.line = ft_strdup(bf);
	tputs(bf, 1, putchar_tc);
}

int	gnl_term(void)
{
	long	c;

	setup_term();
	signal(SIGINT, signals);
	signal(SIGQUIT, signals);
	c = 0;
	g_exist.tmp_hist = NULL;
	g_exist.tmp_line = NULL;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c >= 32 && c <= 126)
			get_printable(c);
		if (c == '\n')
			break ;
		handle_keys(c);
		c = 0;
	}
	if (g_exist.tmp_line)
		ft_free(&g_exist.tmp_line);
	if (!g_exist.line)
		g_exist.line = ft_strdup("");
	add_hist(g_exist.line);
	tputs("\n", 1, putchar_tc);
	return (1);
}
