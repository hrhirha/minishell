/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 16:54:11 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_cd2(t_command *command, t_minishell *minishell)
{
	char	*pwd;

	if (chdir(command->full_args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(command->full_args[1], 2);
		print_error();
		g_exist.last_exec = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_putstr_fd("minishell: cd: error retrieving current directory: \
			getcwd: cannot access parent directories: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			set_pwd_oldpwd(pwd, minishell, 2);
		}
		else
		{
			set_pwd_oldpwd(pwd, minishell, 1);
			g_exist.last_exec = 0;
		}
		free(pwd);
	}
}

void	shell_cd3(t_minishell *minishell)
{
	char	*home;

	home = get_env_value("HOME", minishell->env);
	if (*home == '\0')
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		g_exist.last_exec = 1;
	}
	else
	{
		chdir(home);
		set_pwd_oldpwd(home, minishell, 1);
	}
	free(home);
}

int	shell_cd(t_command *command, t_minishell *minishell)
{
	char	*home;

	if (command->full_args[1] == NULL)
	{
		shell_cd3(minishell);
	}
	else if (command->full_args[1][0] == '\0')
	{
		home = get_env_value("PWD", minishell->env);
		set_pwd_oldpwd(home, minishell, 1);
		free(home);
	}
	else
		shell_cd2(command, minishell);
	return (1);
}
