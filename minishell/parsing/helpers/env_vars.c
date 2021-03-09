/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:09:53 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/09 10:09:55 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_env(char **s, t_data *data)
{
	int x;
	int	i;

	x = 0;
	while (s[x])
		x++;
	data->command->env = malloc((x + 1) * sizeof(char *));
	if (!data->command->env)
		exit_errno(ENOMEM);
	i = 0;
	while (i < x)
	{
		data->command->env[i] = ft_strdup(s[i]);
		i++;
	}
	data->command->env[i] = NULL;
}

char	*get_env_value(char *key, char **env)
{
	char	*env_key;
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	env_value = ft_calloc(1, 1);
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		env_key = ft_substr(env[i], 0, j);
		if (ft_strcmp(key, env_key) == 0)
			break ;
		free(env_key);
		i++;
	}
	if (env[i])
	{
		free(env_value);
		env_value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
		free(env_key);
	}
	return (env_value);
}
