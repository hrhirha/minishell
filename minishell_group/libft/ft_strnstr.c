/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/25 18:49:45 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	helper1(char *str_temp, char *to_find_temp, size_t len, size_t i)
{
	size_t	j;

	j = 0;
	while (*to_find_temp != '\0')
	{
		if (*str_temp != *to_find_temp || (i + j) >= len)
			break ;
		str_temp++;
		to_find_temp++;
		j++;
	}
	return (*to_find_temp);
}

char		*ft_strnstr(const char *ha, const char *ne, size_t len)
{
	size_t	i;

	if (*ne == '\0')
		return ((char*)ha);
	i = 0;
	while (i < len && *ha != '\0')
	{
		if (*ha == *ne)
		{
			if (helper1((char*)ha, (char*)ne, len, i) == '\0')
				return ((char*)ha);
		}
		ha++;
		i++;
	}
	return (0);
}
