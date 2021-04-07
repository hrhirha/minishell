/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/17 17:37:12 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_str_int(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	n;

	i = 0;
	signe = 1;
	n = 0;
	if ((int)str[i] == 45 || (int)str[i] == 43)
	{
		if (str[i] == 45)
			signe = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return ((long long)(n * signe));
}

int			check_int(char *str)
{
	int	i;

	if ((int)str[0] == 45 || (int)str[0] == 43)
		i = 1;
	else
		i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int			shell_exit1(t_command *command)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(command->full_args[1], 2);
	ft_putstr_fd(": numeric argument required \n", 2);
	exit(255);
}

int			shell_exit2(t_command *command)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(command->full_args[1], 2);
	ft_putstr_fd(": numeric argument required \n", 2);
	exit(255);
}

int			shell_exit(t_command *command)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", 2);
	exit_code = g_exist.last_exec;
	if (command->full_args[1] == NULL)
		exit(exit_code);
	else if (check_int(command->full_args[1]) == 1 &&
		command->full_args[2] == NULL)
	{
		exit_code = ft_str_int(command->full_args[1]);
		if (((command->full_args[1][0] != '-' && exit_code < 0) ||
			ft_strlen(command->full_args[1]) > 19) ||
			((command->full_args[1][0] == '-' && exit_code > 0) ||
			ft_strlen(command->full_args[1]) > 19))
			shell_exit1(command);
		exit(exit_code % 256);
	}
	else if (check_int(command->full_args[1]) == 0)
		shell_exit2(command);
	ft_putstr_fd("minishell: exit: too many arguments \n", 2);
	g_exist.last_exec = 1;
	return (1);
}
