/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:38:02 by mobaz             #+#    #+#             */
/*   Updated: 2020/12/10 17:03:44 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *x, const char *y)
{
	while (*x)
	{
		if (*x != *y)
			break ;
		x++;
		y++;
	}
	return (*(const unsigned char *)x - *(const unsigned char *)y);
}

int	ft_strcmp2(const char *x, const char *y)
{
	if (x)
	{
		while (*x)
		{
			if (*x != *y)
				break ;
			x++;
			y++;
		}
		return (*(const unsigned char *)x - *(const unsigned char *)y);
	}
	else
		return (-1);
}
