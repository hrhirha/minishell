/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/25 17:19:37 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_tmp;

	n_tmp = n;
	if (n < 0)
	{
		n_tmp = n * -1;
		ft_putchar_fd('-', fd);
	}
	if (n_tmp <= 9)
	{
		ft_putchar_fd(n_tmp + '0', fd);
	}
	if (n_tmp > 9)
	{
		ft_putnbr_fd(n_tmp / 10, fd);
		ft_putchar_fd(n_tmp % 10 + '0', fd);
	}
}
