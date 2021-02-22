/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:03:08 by hrhirha           #+#    #+#             */
/*   Updated: 2019/10/31 10:00:55 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	if ((size_t)(src - dest) < n)
		ft_memcpy(dest, src, n);
	else
	{
		while (--n > 0)
			str1[n] = str2[n];
		str1[n] = str2[n];
	}
	return (dest);
}
