/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:14:42 by hrhirha           #+#    #+#             */
/*   Updated: 2021/04/09 11:14:43 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_term.h"

int	putchar_tc(int c)
{
	write(1, &c, 1);
	return (c);
}

void	backspace(void)
{
	char	*tmp;

	tmp = g_exist.line;
	tputs(tgetstr("le", NULL), 1, putchar_tc);
	tputs(tgetstr("dc", NULL), 1, putchar_tc);
	g_exist.line = ft_substr(g_exist.line, 0, ft_strlen(g_exist.line) - 1);
	free(tmp);
}

void	handle_keys(long c)
{
	if (c == 4 && (!g_exist.line || !*g_exist.line))
	{
		tcsetattr(0, TCSANOW, &g_exist.tc.init);
		printf("exit\n");
		exit(0);
	}
	if (c == 127 && g_exist.line && *g_exist.line)
		backspace();
	if (c == 4283163)
		up_hist();
	if (c == 4348699)
		down_hist();
}
