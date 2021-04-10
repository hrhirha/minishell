/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/26 00:35:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_num(char *str, char c)
{
	int			words;
	int			length;

	words = 0;
	length = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == c)
			words = 0;
		else if (words == 0)
		{
			words = 1;
			length++;
		}
		str++;
	}
	return (length);
}

static int	word_length(char *str, int i, char c)
{
	int			length;

	length = 0;
	while (str[i] != c && str[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

static	void	*wrds_free(char **wrds, int j)
{
	while (j--)
		free(wrds[j]);
	free(wrds);
	return (NULL);
}

static char	**alloc_wrds(char **wrds, char const *s, char c)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < words_num((char *)s, c))
	{
		k = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		wrds[j] = ft_calloc(word_length((char *)s, i, c) + 1, sizeof(char));
		if (wrds[j] == NULL)
		{
			wrds_free(wrds, j);
			return (NULL);
		}
		while (s[i] != c && s[i] != '\0')
		{
			wrds[j][k++] = s[i++];
		}
		wrds[j++][k] = '\0';
	}
	wrds[j] = 0;
	return (wrds);
}

char	**ft_split(char const *s, char c)
{
	char		**wrds;

	if (s == NULL)
		return (NULL);
	wrds = ft_calloc(words_num((char *)s, c) + 1, sizeof(char *));
	if (wrds == NULL)
		return (NULL);
	alloc_wrds(wrds, s, c);
	return (wrds);
}
