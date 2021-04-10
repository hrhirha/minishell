/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_hist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:14:17 by hrhirha           #+#    #+#             */
/*   Updated: 2021/04/09 11:14:19 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_term.h"

void	add_hist(char *s)
{
	t_hist	*new;

	if (!s || !*s)
		return ;
	if (!g_exist.hist)
	{
		g_exist.hist = malloc(sizeof(t_hist));
		if (!g_exist.hist)
			return ;
		g_exist.hist->s = ft_strdup(s);
		g_exist.hist->next = NULL;
		g_exist.hist->prev = NULL;
		return ;
	}
	new = malloc(sizeof(t_hist));
	if (!new)
		return ;
	new->s = ft_strdup(s);
	new->next = g_exist.hist;
	new->prev = NULL;
	g_exist.hist->prev = new;
	g_exist.hist = new;
}

void	up_hist(void)
{
	int		len;
	char	*tmp;

	if (!g_exist.hist)
		return ;
	if (g_exist.line && !g_exist.tmp_hist)
		g_exist.tmp_line = ft_strdup(g_exist.line);
	if (!g_exist.tmp_hist)
		g_exist.tmp_hist = g_exist.hist;
	else if (g_exist.tmp_hist->next)
		g_exist.tmp_hist = g_exist.tmp_hist->next;
	len = 0;
	if (g_exist.line)
		len = ft_strlen(g_exist.line);
	while (--len >= 0)
		backspace();
	tmp = g_exist.line;
	g_exist.line = ft_strdup(g_exist.tmp_hist->s);
	free(tmp);
	tputs(g_exist.line, 1, putchar_tc);
}

void	line_form_hist(void)
{
	char	*tmp;

	g_exist.tmp_hist = g_exist.tmp_hist->prev;
	tmp = g_exist.line;
	g_exist.line = ft_strdup(g_exist.tmp_hist->s);
	free(tmp);
	tputs(g_exist.line, 1, putchar_tc);
}

void	backedup_line(void)
{
	char	*tmp;

	tmp = g_exist.line;
	g_exist.line = ft_strdup(g_exist.tmp_line);
	ft_free(&g_exist.tmp_line);
	free(tmp);
	g_exist.tmp_hist = NULL;
	tputs(g_exist.line, 1, putchar_tc);
}

void	down_hist(void)
{
	int		len;

	if (!g_exist.tmp_hist)
		return ;
	len = 0;
	if (g_exist.line)
		len = ft_strlen(g_exist.line);
	while (--len >= 0)
		backspace();
	if (g_exist.tmp_hist->prev)
		line_form_hist();
	else if (g_exist.tmp_line)
		backedup_line();
	else
	{
		g_exist.tmp_hist = NULL;
		ft_free(&g_exist.line);
	}
}
