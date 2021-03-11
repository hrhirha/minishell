/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spec_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:25:56 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/09 10:25:58 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	scan_str(char **s, char **env)
{
	int		i;
	char	*scaned_str;
	char	*tmp_s;
	char	*sub;
	char	*tmp;

	tmp_s = *s;
	scaned_str = ft_calloc(1, 1);
	i = 0;
	while (tmp_s[i])
	{
		if (tmp_s[i] == '"')
			sub = handle_dquotes(tmp_s, &i, env);
		else if (tmp_s[i] == '\'')
			sub = handle_squotes(tmp_s, &i);
		else
			sub = handle_noquotes(tmp_s, &i, env);
		tmp = scaned_str;
		scaned_str = ft_strjoin(scaned_str, sub);
		free(tmp);
		free(sub);
	}
	*s = ft_strdup(scaned_str);
	free(tmp_s);
	free(scaned_str);
}

void	scan_redirs(t_list *redirs, char **env)
{
	t_list			*tmp_redirs;
	t_redirection	*redir;

	tmp_redirs = redirs;
	while (tmp_redirs)
	{
		t_exist.dir = 1;
		redir = (t_redirection *)tmp_redirs->content;
		scan_str(&redir->file_name, env);
		tmp_redirs = tmp_redirs->next;
	}
}

void	scan_command(t_list *pipes, char **env)
{
	int				i;
	t_list			*tmp;
	t_command		*cmd;

	tmp = pipes;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		scan_redirs(cmd->redirections, env);
		i = 0;
		if (cmd->full_args)
		{
			while (cmd->full_args[i])
			{
				t_exist.dir = 0;
				scan_str(&cmd->full_args[i], env);
				if (t_exist.quote)
					i += split_arg_exp(i, cmd);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
}
