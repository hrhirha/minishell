/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2020/01/07 22:38:54 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_atoi(const char *str)
{
	long	sum;
	int		negative;

	if (!str)
		return (0);
	negative = 1;
	sum = 0;
	while (*str != '\0' && (*str == '\t' || *str == '\n' || *str == '\r' ||
	*str == '\v' || *str == '\f' || *str == ' '))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		sum = (sum * 10) + (*str - '0');
		if ((sum * negative) > 2147483647)
			return (-1);
		else if ((sum * negative) < -2147483648)
			return (0);
		++str;
	}
	sum = sum * negative;
	return ((int)sum);
}
