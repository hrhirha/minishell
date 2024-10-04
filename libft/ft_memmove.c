/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/26 22:25:24 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src_temp;
	char	*dst_temp;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	src_temp = (char *)src;
	dst_temp = (char *)dst;
	i = 0;
	if (src < dst)
		while (len--)
			dst_temp[len] = src_temp[len];
	else if (src > dst)
	{
		while (i < len)
		{
			dst_temp[i] = src_temp[i];
			i++;
		}
	}
	return (dst);
}
