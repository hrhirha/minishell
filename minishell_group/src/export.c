/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/17 17:37:12 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export_invalid_arg_msg(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exist.last_exec = 1;
}

int valid_arg_export(char *str)
{
	char **args;
	int i;

	if(str[0] == '\0')
		return (1);
	if(ft_isdigit(str[0]) == 1)
		return (1);
	args = ft_split(str, '=');
	i = 0;
	while (args[0][i] != '\0')
	{
		if (ft_isalnum(args[0][i]) != 1 && args[0][i] != '_')
		{
			free_double(args);
			return (1);
		}
		i++;
	}
	free_double(args);
	return (0); 
}

int	arg_has_equal(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if(arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void  export_varible(char *arg, t_minishell *minishell)
{
	char **new_env;
	int i;
	
	new_env = (char **)malloc(sizeof(char *) * (words_counter(minishell->env) + 2));
	i = 0;
	while (minishell->env[i] != NULL)
	{
		new_env[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	free_double(minishell->env);
	minishell->env = new_env;
}

char		*env_value(char *arg)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if(arg[i] == '=')
			return (&arg[i+1]);
		i++;
	}
	return (NULL);
}

int export_env_compair(char *var1, char *var2)
{
	int		res;
	char	**str1;
	char	**str2;
	
	if(!var1 && !var2)
		return (0);
	res = 0;
	str1 = ft_split(var1, '=');
	str2 = ft_split(var2, '=');
	if (ft_strcmp(str1[0], str2[0]) == 0)
		res = 1;
	free_double(str1);
	free_double(str2);
	return (res);

}

int export_arg_exist(char *full_arg, t_minishell *minishell)
{
	int i;
	
	i = 0;
	while (minishell->env[i] != NULL)
	{
		if(export_env_compair(minishell->env[i], full_arg) == 1)
			return (0);
		i++;
	}
	return (1);
}

void  export_varible_edit(char *arg, t_minishell *minishell)
{
	char *tmp;
	int i;
	
	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (export_env_compair(minishell->env[i], arg) ==  1)
		{
			free(minishell->env[i]);
			minishell->env[i] = ft_strdup(arg);
			return ;
		}
		i++;
	}
}

void	display_env_chars(char *env)
{
	int len;
	int i;
	int first;

	first = 0;
	len = ft_strlen(env);
	i = 0;
	while (i < len)
	{
		if((env[i] == 61) && (first == 0))
		{
			ft_putchar_fd(env[i], 1);
			ft_putchar_fd('"', 1);
			first = 1;
		}
		else
			ft_putchar_fd(env[i], 1);
		i++;
	}
	if(first == 1)
		ft_putchar_fd('"', 1);
}

void	ex_helper2(char **env)
{
	int j;

	j = 0;
	while (env[j] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		display_env_chars(env[j]);
		ft_putchar_fd('\n', 1);
		j++;
	}
}

int		display_env_ordred(char **env)
{
	char	*temp;
	int		count;
	int		i;
	int		j;

	count = words_counter(env);
	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	ex_helper2(env);
	return (0);
}

int		shell_export(t_command *command, t_minishell *minishell)
{
	int i;

	if (command->full_args[1] == NULL)
	{
		display_env_ordred(minishell->env);
		return (1);
	}
	// else if (command->full_args[1][0] == '\0')
	// 	return (1);
	i = 1;
	while (command->full_args[i] != NULL)
	{
		if(valid_arg_export(command->full_args[i]) == 1)
			export_invalid_arg_msg(command->full_args[i]);
		else if (arg_has_equal(command->full_args[i]) == 1)
		{
			if (export_arg_exist(command->full_args[i], minishell) == 0)
				export_varible_edit(command->full_args[i], minishell);	
			else
				export_varible(command->full_args[i], minishell);	
		}
		else if (export_arg_exist(command->full_args[i], minishell) == 1) // 1 ==> doesn't exist
		{
			export_varible(command->full_args[i], minishell);	
		}
		i++;
	}
	return (1);
}
