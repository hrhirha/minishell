/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/22 00:17:30 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		found;
	char	*str;
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	found = 0;
	while (s_len--)
	{
		if (*s == c)
		{
			found = 1;
			str = (char *)s;
		}
		s++;
	}
	if (found == 1)
		return (str);
	else
		return (0);
}
