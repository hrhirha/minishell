/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2020/01/08 20:03:52 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*help1(void)
{
	char	*hex;

	hex = malloc(2);
	hex[0] = '0';
	hex[1] = '\0';
	return (hex);
}

char	*ft_hexconv(unsigned int c)
{
	char	*hex;
	int		i;
	int		temp;

	i = 0;
	if (c == 0)
		return (help1());
	hex = (char *)malloc(sizeof(char) * 20);
	while (c)
	{
		temp = c % 16;
		if (temp < 10)
			hex[i++] = temp + 48;
		else
			hex[i++] = temp + 55;
		c /= 16;
	}
	hex[i] = '\0';
	hex = ft_strrev(hex);
	return (hex);
}

char	*help2(char *p)
{
	char	*hex;

	if (p)
	{
		hex = malloc(3);
		hex[0] = '0';
		hex[1] = 'x';
		hex[2] = '\0';
	}
	else
	{
		hex = malloc(4);
		hex[0] = '0';
		hex[1] = 'x';
		hex[2] = '0';
		hex[3] = '\0';
	}
	return (hex);
}

int	help3(char **hex, size_t c)
{
	char	*hex_tmp;
	int		temp;
	int		i;

	hex_tmp = *hex;
	i = 0;
	while (c)
	{
		temp = c % 16;
		if (temp < 10)
		{
			hex_tmp[i] = temp + 48;
			i++;
		}
		else
		{
			hex_tmp[i] = temp + 55;
			i++;
		}
		c /= 16;
	}
	return (i);
}

char	*ft_hexconv_p(size_t c, char *p)
{
	char	*hex;
	int		i;

	if (c == 0)
		return (help2(p));
	hex = (char *)malloc(20);
	i = help3(&hex, c);
	hex[i++] = 'x';
	hex[i++] = '0';
	hex[i] = '\0';
	hex = ft_strrev(hex);
	return (hex);
}
