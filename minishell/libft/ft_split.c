/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:55:11 by hrhirha           #+#    #+#             */
/*   Updated: 2019/11/05 22:19:23 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_substrs(char const *s, char c)
{
	int i;
	int scount;

	i = 0;
	scount = 0;
	if (s[i] == '\0')
		return (scount);
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
			if (s[i] == '\0')
				return (scount);
		}
		if (s[i] != c)
			i++;
		if (s[i] == c && s[i] != '\0')
			scount++;
	}
	scount++;
	return (scount);
}

static	int		ft_count_chars(char const *s, char c)
{
	int i;
	int ccount;

	i = 0;
	ccount = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		ccount++;
	}
	return (ccount);
}

static	char	**ft_free_arr(char **arr, int scount)
{
	while (scount >= 0)
	{
		free(arr[scount]);
		scount--;
	}
	free(arr);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		scount;
	char	**arr;

	i = 0;
	scount = 0;
	if (s == NULL)
		return (NULL);
	if (!(arr = (char **)malloc((ft_count_substrs(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (scount < ft_count_substrs(s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		if (!(arr[scount] = (char *)malloc(((ft_count_chars(&s[i], c) + 1)
							* sizeof(char)))))
			return (ft_free_arr(arr, scount));
		while (s[i] != c && s[i] != '\0')
			arr[scount][j++] = s[i++];
		arr[scount++][j] = '\0';
	}
	arr[scount] = NULL;
	return (arr);
}
