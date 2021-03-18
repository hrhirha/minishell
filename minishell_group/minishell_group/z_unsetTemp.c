/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_unsetTemp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/17 17:37:12 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int vars_counter_(char **new_vars, char **env)
{
	int i;
	int j;
	int counter;

	counter = 0;
	i = 0;
	while (new_vars[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			if(env_compair(new_vars[i], env[j]) == 1)
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}

int is_valid_arg2(char *arg, int show_error)
{

	// else if (it starts with something other than char), show error
	if(arg_start_with_char(arg) == 0) // TODO: crate this
	{
		return (1);
	}
	else
	{
		// if show_error == 1 ===> show errors
		if(show_error == 1)
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exist.last_exec = 1;
		}
		return (0);
	}
	return (0);
}

int count_valid_args2(char **args)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if(is_valid_arg2(args[i], 0) == 0)
			len++;
		i++;
	}
	return (len);
}

char **set_valid_envs2(t_command *command)
{
	int i;
	int j;
	char **new_env;
	int len;

	len = count_valid_args2(&(command->full_args[1]));
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 1;
	j = 0;
	while (command->full_args[i] != NULL)
	{
		if(is_valid_arg2(command->full_args[i], 1) == 1)
		{
			new_env[j] = ft_strdup(command->full_args[i]);
			j++;
		}
		
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}


int		keep_env(char *arg, char **args)
{
	int i;

	i = 0;
	while (args[i] != NULL)
	{
		if(env_compair(args[i], arg) == 1) // if exist
			return (0);
		i++;
	}
	return (1);
}

int shell_unset(t_command *command, t_minishell *minishell)
{

// TODO: export many variables exm: export A=123 B=345 .....
// TODO: check if they don't start with a number
// TODO: chat they have '=' without spaces
// TODO: if the variable already exist then upadate it


	
	char **env_tmp;
	int env_len;
	int i;
	int new_vars;
	int j;
	char **interm;

	// char **new_env;




	
	interm = set_valid_envs2(command);

	new_vars = vars_counter_(interm, minishell->env); // argsNum that needs to be unset


	
	env_len = words_counter(minishell->env);
	env_tmp = (char **)malloc(sizeof(char *) * (env_len - new_vars + 1));



	
	i = 0;
	j = 0;
	while(minishell->env[i] != NULL)
	{
		if(keep_env(minishell->env[i], interm) == 1)
		{
			env_tmp[j] = ft_strdup(minishell->env[i]);
			j++;	
		}
		i++;
	}

	env_tmp[j] = NULL;

	
	// free_double(new_env);
	free_double(minishell->env);
	free_double(interm);
	minishell->env = env_tmp;
	return (1);
}
