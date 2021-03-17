/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:13:23 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/17 17:37:15 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_errno(int errnum)
{
	errno = errnum;
	exit(errno);
}

int		error(int errnum, char c)
{
	int	err;

	err = 0;
	if (errnum == SNTXERR)
	{
		ft_putstr_fd("minishell: syntax error near ", 1);
		if (c == '\0')
			ft_putstr_fd("'newline'", 1);
		ft_putchar_fd(c, 1);
		ft_putchar_fd('\n', 1);
		err = 1;
	}
	return (err);
}
