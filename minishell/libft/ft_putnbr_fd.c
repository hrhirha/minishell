/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:55:11 by hrhirha           #+#    #+#             */
/*   Updated: 2019/10/29 10:27:37 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int un;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	un = n;
	if (un < 10)
		ft_putchar_fd(un + 48, fd);
	if (un >= 10)
	{
		ft_putnbr_fd(un / 10, fd);
		ft_putchar_fd(un % 10 + 48, fd);
	}
}
