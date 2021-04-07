#include "../minishell.h"

int		putchar_tc(int c)
{
	write(1, &c, 1);
	return (c);
}

void	setup_term()
{
	g_exist.tc.name = getenv("TERM");
	if (!g_exist.tc.name)
		printf("TERM not set\n");
	tgetent(NULL, g_exist.tc.name);
	tcgetattr(0, &g_exist.tc.init);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_exist.tc.term);
	g_exist.tc.term.c_lflag = g_exist.tc.term.c_lflag & ~ICANON;
	g_exist.tc.term.c_lflag = g_exist.tc.term.c_lflag & ~ECHO;
	g_exist.tc.term.c_cc[VMIN] = 1;
	g_exist.tc.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_exist.tc.term);
	g_exist.tc.cm = tgetstr("cm", NULL);
	g_exist.tc.ce = tgetstr("ce", NULL);
	g_exist.tc.dl = tgetstr("dl", NULL);
}

void	get_printable(char **line, long c)
{
	char	bf[2];
	char	*tmp;

	bf[0] = c;
	bf[1] = '\0';
	if (*line)
	{
		tmp = *line;
		*line = ft_strjoin(*line, bf);
		free(tmp);
	}
	else
		*line = ft_strdup(bf);
	tputs(bf, 1, putchar_tc);
}

void	backspace(char **line)
{
	char *tmp = *line;

	tputs(tgetstr("le", NULL), 1, putchar_tc);
	tputs(tgetstr("dc", NULL), 1, putchar_tc);
	*line = ft_substr(*line, 0, ft_strlen(*line) - 1);
	free(tmp);
}

void	up_key(char **line)
{
	(void)line;
	*line = ft_strdup(g_exist.tmp_hist->s);
	g_exist.tmp_hist = g_exist.tmp_hist->next;
	// tputs(tgetstr("dl", NULL), 1, putchar_tc);
	tputs(*line, 1, putchar_tc);
}
void	down_key(char **line)
{
	(void)line;
	if (!g_exist.tmp_hist->prev)
		return ;
	g_exist.tmp_hist = g_exist.tmp_hist->prev;
	*line = ft_strdup(g_exist.tmp_hist->s);
	// tputs(tgetstr("dl", NULL), 1, putchar_tc);
	tputs(*line, 1, putchar_tc);
}

int	gnl_term(char **line)
{
	long	c;

	setup_term();
	c = 0;
	g_exist.tmp_hist = g_exist.hist;
	while (read(0, &c, sizeof(c)) > 0)
	{
		// printf("%ld\n", c);
		if (c >= 32 && c <= 126)
			get_printable(line, c);
		if (c == '\n')
			break ;
		if (c == 4 && !*line)
		{
			// exit(0);
		}
		if (c == 127 && *line && **line)
			backspace(line);
		if(c == 4283163 && g_exist.tmp_hist)
			up_key(line);
		if (c == 4348699 && g_exist.tmp_hist)
			down_key(line);
		c = 0;
	}
	add_hist(*line);
	printf("\n");
	if (!*line)
		*line = ft_strdup("");
	return(1);
}