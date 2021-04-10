/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/12/23 16:12:05 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	numlen(long num)
{
	long	len;

	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = num * -1;
		len = 1;
	}
	else
		len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	helper(char *temp, int i, long nb)
{
	long	copy;
	long	size;

	copy = nb;
	size = 1;
	copy /= 10;
	while (copy > 0)
	{
		copy /= 10;
		size *= 10;
	}
	while (size > 0)
	{
		temp[i] = nb / size + '0';
		i++;
		nb %= size;
		size /= 10;
	}
	temp[i] = '\0';
}

char	*ft_itoa(int nb)
{
	char	*temp;
	int		i;
	long	nb_tmp;

	nb_tmp = nb;
	temp = malloc(numlen(nb_tmp) + 1);
	if (temp == NULL)
		return (NULL);
	if (nb == 0)
	{
		temp[0] = '0';
		temp[1] = '\0';
		return (temp);
	}
	i = 0;
	if (nb_tmp < 0)
	{
		temp[i] = '-';
		nb_tmp = nb_tmp * -1;
		i++;
	}
	helper(temp, i, nb_tmp);
	return (temp);
}
