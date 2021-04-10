/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/26 00:37:42 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*temp;
	int			i;

	if (!s)
		return (NULL);
	temp = (char *)malloc(ft_strlen(s) + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		temp[i] = f(i, s[i]);
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
