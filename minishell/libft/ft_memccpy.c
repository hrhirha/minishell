/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/22 19:16:04 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_temp;
	unsigned char	*src_temp;
	unsigned char	c1;

	dst_temp = (unsigned char *)dst;
	src_temp = (unsigned char *)src;
	c1 = (unsigned char)c;
	while (n--)
	{
		if (*src_temp == c1)
		{
			*dst_temp = *src_temp;
			return (++dst_temp);
		}
		*dst_temp = *src_temp;
		dst_temp++;
		src_temp++;
	}
	return (NULL);
}
