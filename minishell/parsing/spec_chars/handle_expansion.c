/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:51:06 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/03 10:51:09 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char *key, char **env)
{
	char	*env_key;
	char	*env_value;
	int 	i;
	int 	j;

	i = 0;
	env_value = ft_calloc(1, 1);
	while (env[i])
	{
		// printf("[%d]%s\n", i, env[i]);
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

char	*handle_env_expansion(char *s, int *i, char **env)
{
	char	*key;
	char	*value;
	int		j;

	*i += 1;
	j = 0;
	while (ft_isalnum(s[*i + j]) == 1 || s[*i + j] == '_')
		j++;
	key = ft_substr(s, *i, j);
	*i += j;
	value = get_env_value(key, env);
	free(key);
	return (value);
}