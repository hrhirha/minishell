/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/22 00:23:31 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char*)s1;
	s2_temp = (unsigned char*)s2;
	i = 0;
	while (i < n && ((*s1_temp != '\0') || (*s2_temp != '\0')))
	{
		if (*s1_temp != *s2_temp)
			return (*s1_temp - *s2_temp);
		s2_temp++;
		s1_temp++;
		i++;
	}
	return (0);
}
