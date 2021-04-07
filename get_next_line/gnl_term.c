#include "gnl_term.h"

void	setup_term()
{
	g_exist.tc.name = getenv("TERM");
	if (!g_exist.tc.name)
		printf("TERM not set\n");
	tgetent(NULL, g_exist.tc.name);
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
		// if (g_exist.tmp_hist)
		// {
		// 	tmp = g_exist.tmp_hist->s;
		// 	g_exist.tmp_hist->s = ft_strdup(*line);
		// 	free(tmp);
		// }
	}
	else
		*line = ft_strdup(bf);
	tputs(bf, 1, putchar_tc);
}

int	gnl_term(char **line)
{
	long	c;

	setup_term();
	c = 0;
	g_exist.tmp_hist = g_exist.hist;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c >= 32 && c <= 126)
			get_printable(line, c);
		if (c == '\n')
			break ;
		handle_keys(line, c);
		c = 0;
	}
	add_hist(*line);
	printf("\n");
	if (!*line)
		*line = ft_strdup("");
	return(1);
}