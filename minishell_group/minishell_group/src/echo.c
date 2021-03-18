/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 15:32:56 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_display(char **full_args, int i)
{
	int br;

	br = i;
	while (full_args[i])
	{
		ft_putstr_fd(full_args[i], 1);
		if (full_args[i + 1])
		{
			ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (br == 1)
		ft_putstr_fd("\n", 1);
}

int		shell_echo2(t_command *command, int i)
{
	int j;
	int br;

	br = 0;
	j = 0;
	if (command->full_args[i][j] == '\0')
		br = 1;
	while (command->full_args[i][j] != '\0')
	{
		if (j == 0 && command->full_args[i][j] != '-')
		{
			br = 1;
			break ;
		}
		else if (j != 0 && command->full_args[i][j] != 'n')
		{
			br = 1;
			break ;
		}
		j++;
	}
	return (br);
}

int		shell_echo(t_command *command, t_minishell *minishell)
{
	int i;
	int br;

	if (command->full_args[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
	}
	else
	{
		br = 0;
		i = 1;
		while (command->full_args[i])
		{
			br = shell_echo2(command, i);
			if (br == 1)
				break ;
			i++;
		}
		echo_display(command->full_args, i);
	}
	g_exist.last_exec = 0;
	return (1);
}
