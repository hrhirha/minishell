/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 16:23:43 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		words_counter(char **env)
{
	int len;

	len = 0;
	while (env[len] != NULL)
		len++;
	return (len);
}

void	check_lower_case(t_command *command)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(command->full_args[0]);
	i = 0;
	while (tmp[i])
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	if (ft_strcmp(tmp, "env") == 0)
	{
		free(command->full_args[0]);
		command->full_args[0] = tmp;
	}
	else
		free(tmp);
}
