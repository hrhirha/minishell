/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:53:00 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 16:38:39 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}

int	tab_size(char **t)
{
	int	i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

void	free_tab(char **t)
{
	int	i;

	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
}

void	init_cmd(t_data *data)
{
	data->simple_cmd = malloc(sizeof(t_command));
	if (!data->simple_cmd)
		exit_errno(ENOMEM);
	data->cmd = ft_calloc(1, 1);
	if (!data->cmd)
		exit_errno(ENOMEM);
	data->simple_cmd->redirections = NULL;
	data->simple_cmd->full_args = NULL;
	data->ac = 0;
}

void	update_env_pwd(t_data *data)
{
	char	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	if (export_arg_exist(pwd, data->command) == 0)
		export_varible_edit(pwd, data->command);
	else
		export_varible(pwd, data->command);
	free(tmp);
	free(pwd);
	unset_varible("OLDPWD", data->command);
	export_varible("OLDPWD", data->command);
}
