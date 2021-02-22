/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:13:23 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/21 18:13:25 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_errno(int errnum)
{
	errno = errnum;
	exit(errno);
}

void	exit_error(int errnum, char c)
{
	if (errnum == SNTXERR)
	{
		ft_putstr_fd("minishell: syntax error near ", 1);
		if (c == '\0')
			ft_putstr_fd("'newline'", 1);
		ft_putchar_fd(c, 1);
		ft_putchar_fd('\n', 1);
	}
	exit(errnum);
}
