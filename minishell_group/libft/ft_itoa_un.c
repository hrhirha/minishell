/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_un.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/12/05 17:53:55 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	numlen(unsigned long num)
{
	unsigned long		len;

	if (num == 0)
		return (1);
	len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void				helper(char *temp, int i, unsigned long nb)
{
	unsigned long		copy;
	unsigned long		size;

	copy = nb;
	size = 1;
	while ((copy /= 10) > 0)
		size *= 10;
	while (size > 0)
	{
		temp[i] = nb / size + '0';
		i++;
		nb %= size;
		size /= 10;
	}
	temp[i] = '\0';
}

char					*ft_itoa_un(unsigned nb)
{
	char				*temp;
	int					i;
	unsigned long		nb_tmp;

	nb_tmp = nb;
	temp = malloc(numlen(nb_tmp) + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	helper(temp, i, nb_tmp);
	return (temp);
}
