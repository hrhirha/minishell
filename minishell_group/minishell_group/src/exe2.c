/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/14 15:44:28 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths2(char **paths, char *tmp, char **env, int i)
{
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp, ':');
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			tmp = &*(env[i] + 5);
			break ;
		}
		i++;
	}
	return (paths);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			tmp = &*(env[i] + 5);
			break ;
		}
		i++;
	}
	return (get_paths2(paths, tmp, env, i));
}

char	*found_exec2(char **paths, char *tmp1)
{
	int			i;
	char		*execter;
	struct stat	stbf;
	struct stat	*statbuf;

	statbuf = &stbf;
	i = 0;
	while (paths[i] != NULL)
	{
		execter = ft_strjoin(paths[i], tmp1);
		if (stat(execter, statbuf) == 0)
		{
			free(tmp1);
			free_double(paths);
			return (execter);
		}
		free(execter);
		i++;
	}
	free(tmp1);
	free_double(paths);
	return (NULL);
}

char	*found_exec(t_command *command, t_minishell *minishell)
{
	char	**paths;
	char	*tmp1;

	tmp1 = ft_strjoin("/", command->full_args[0]);
	paths = get_paths(minishell->env);
	if (paths == NULL)
		return (NULL);
	return (found_exec2(paths, tmp1));
}

int		ft_str_has_char(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	while (s_len--)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
