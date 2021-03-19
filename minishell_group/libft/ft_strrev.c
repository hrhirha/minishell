/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2020/01/07 22:42:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	int		len;
	int		i;
	char	temp;

	len = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (i < (len / 2))
	{
		temp = str[i];
		str[i] = str[len - (i + 1)];
		str[len - (i + 1)] = temp;
		i++;
	}
	return (str);
}
