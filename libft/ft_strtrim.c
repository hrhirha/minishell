/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/26 21:22:50 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charexist(const char c, const char *s)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static long	ft_strtrimlen(char const *s1, char const *set)
{
	long	s0_len;
	long	s1_len;
	long	i;
	long	j;

	if (s1 == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (!ft_charexist(s1[i], set))
			break ;
		i++;
	}
	s0_len = ft_strlen(s1);
	s1_len = s0_len;
	j = 0;
	while (s1_len--)
	{
		if (!ft_charexist(s1[s1_len], set))
			break ;
		j++;
	}
	return (s0_len - (i + j));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	long	ln;
	char	*temp;

	if (s1 == NULL || set == NULL)
		return (NULL);
	ln = ft_strtrimlen(s1, set);
	if (ln == 0 || ln < 0)
		return (ft_strdup(""));
	temp = malloc((ln + 1));
	if (temp == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		if (!ft_charexist(*s1, set))
		{
			ft_strcpy(temp, (char *)s1);
			temp[ln] = '\0';
			break ;
		}
		s1++;
	}
	return (temp);
}
