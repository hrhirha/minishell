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

int	help99(int *pwd, int *oldpwd, char **env)
{
	int	j;

	*oldpwd = 0;
	while (env[*oldpwd])
	{
		if (search_env("OLDPWD", env, *oldpwd, &j) == 0)
			break ;
		*oldpwd += 1;
	}
	*pwd = 0;
	while (env[*pwd])
	{
		if (search_env("PWD", env, *pwd, &j) == 0)
			break ;
		*pwd += 1;
	}
	free(env[*oldpwd]);
	return (j);
}
