#include "../minishell.h"

void	add_hist(char *s)
{
	t_hist *new;

	if (!s)
		return ;
	if (!g_exist.hist)
	{
		g_exist.hist = malloc(sizeof(t_hist));
		g_exist.hist->s = ft_strdup(s);
		g_exist.hist->next = NULL;
		g_exist.hist->prev = NULL;
		return ;
	}
	new = malloc(sizeof(t_hist));
	new->s = ft_strdup(s);
	new->next = g_exist.hist;
	g_exist.hist->prev = new;
	g_exist.hist = new;
}

void	add_tmp_hist(char *s)
{
	t_hist *new;

	if (!s)
		return ;
	if (!g_exist.hist)
	{
		g_exist.tmp_hist = malloc(sizeof(t_hist));
		g_exist.tmp_hist->s = ft_strdup(s);
		g_exist.tmp_hist->next = NULL;
		g_exist.tmp_hist->prev = NULL;
		return ;
	}
	new = malloc(sizeof(t_hist));
	new->s = ft_strdup(s);
	new->next = g_exist.tmp_hist;
	g_exist.tmp_hist->prev = new;
	g_exist.tmp_hist = new;
}
