#include "gnl_term.h"

int		putchar_tc(int c)
{
	write(1, &c, 1);
	return (c);
}

void	backspace(char **line)
{
	char *tmp;

	tmp = *line;
	tputs(tgetstr("le", NULL), 1, putchar_tc);
	tputs(tgetstr("dc", NULL), 1, putchar_tc);
	*line = ft_substr(*line, 0, ft_strlen(*line) - 1);
	free(tmp);
}

void	up_key(char **line)
{
	int		len;
	char	*tmp;

	if (!*line)
		*line = ft_strdup("");
	if (!g_exist.tmp_hist->prev)
	{
		// g_exist.tmp_line = ft_strdup(*line);
		add_tmp_hist(*line);
	}
	if (!g_exist.tmp_hist->next)
		return ;
	g_exist.tmp_hist = g_exist.tmp_hist->next;
	len = 0;
	if (*line)
		len = ft_strlen(*line);
	while (--len >= 0)
		backspace(line);
	tmp = *line;
	*line = ft_strdup(g_exist.tmp_hist->s);
	free(tmp);
	tputs(*line, 1, putchar_tc);
}

void	down_key(char **line)
{
	int		len;
	char	*tmp;

	if (!g_exist.tmp_hist->prev)
	{
		// while (--len >= 0)
		// 	backspace(line);
		// tmp = *line;
		// *line = ft_strdup(g_exist.tmp_line);
		// free(tmp);
		// tputs(*line, 1, putchar_tc);
		return ;
	}
	g_exist.tmp_hist = g_exist.tmp_hist->prev;
	len = 0;
	if (*line)
		len = ft_strlen(*line);
	while (--len >= 0)
		backspace(line);
	tmp = *line;
	*line = ft_strdup(g_exist.tmp_hist->s);
	free(tmp);
	tputs(*line, 1, putchar_tc);
}

void	handle_keys(char **line, long c)
{
	if (c == 4 && (!*line || !**line))
	{
		tcsetattr(0, TCSANOW, &g_exist.tc.init);
		printf("exit\n");
		exit(0);
	}
	if (c == 127 && *line && **line)
		backspace(line);
	if(c == 4283163 && g_exist.tmp_hist)
		up_key(line);
	if (c == 4348699 && g_exist.tmp_hist)
		down_key(line);
}
