/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/12/16 17:39:19 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*temp;

	if (!s1 && !s2)
		return (NULL);
	temp = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	j = 0;
	i = 0;
	if (s1 != NULL)
		while (s1[i] != '\0')
			temp[j++] = s1[i++];
	i = 0;
	if (s2 != NULL)
		while (s2[i] != '\0')
			temp[j++] = s2[i++];
	temp[j] = '\0';
	return (temp);
}
