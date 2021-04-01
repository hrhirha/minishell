/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spec_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:25:56 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 17:00:15 by ler-rech         ###   ########.fr       */
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
		g_exist.dir = 1;
		redir = (t_redirection *)tmp_redirs->content;
		scan_str(&redir->file_name, env);
		tmp_redirs = tmp_redirs->next;
	}
}

void	scan_args(t_command *cmd, char **env)
{
	int	exp;
	int	i;

	i = 0;
	while (cmd->full_args[i])
	{
		exp = 0;
		g_exist.dir = 0;
		if (ft_strchr(cmd->full_args[i], '$'))
			exp = 1;
		scan_str(&cmd->full_args[i], env);
		if (!*cmd->full_args[i] && exp)
			i++;
		else if (g_exist.quote && exp)
			i += split_arg_exp(i, cmd);
		else
			i++;
	}
}

void	scan_command(t_list *pipes, char **env)
{
	t_list		*tmp;
	t_command	*cmd;

	tmp = pipes;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		scan_redirs(cmd->redirections, env);
		if (cmd->full_args)
		{
			scan_args(cmd, env);
		}
		tmp = tmp->next;
	}
}
