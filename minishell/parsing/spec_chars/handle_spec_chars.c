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
		redir = (t_redirection *)tmp_redirs->content;
		t_exist.dir = 1;
		scan_str(&redir->file_name, env);
		tmp_redirs = tmp_redirs->next;
	}
}

int		tab_size(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}


int		split_arg_exp(int i, t_command *cmd)
{
	char	**tab;
	char	**new_args;
	int		j;
	int		k;

	j = 0;
	while (cmd->full_args[i][j])
	{
		if (cmd->full_args[i][j] == '\t')
			cmd->full_args[i][j] = ' ';
		j++;
	}
	tab = ft_split(cmd->full_args[i], ' ');
	new_args = malloc((tab_size(cmd->full_args)
			+ tab_size(tab)) * sizeof(char *));
	j = -1;
	while (++j < i)
		new_args[j] = ft_strdup(cmd->full_args[j]);
	k = 0;
	while (tab[k])
	{
		new_args[j++] = ft_strdup(tab[k++]);
	}
	while (cmd->full_args[++i])
	{
		new_args[j] = ft_strdup(cmd->full_args[i]);
		j++;
	}
	new_args[j] = NULL;
	// free (tab)
	// free (cmd->full_args)
	cmd->full_args = new_args;
	return (tab_size(tab));
}

void    scan_command(t_list *pipes, char **env)
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
				// printf("i = %d\n", i);
				if (t_exist.quote)
					i += split_arg_exp(i, cmd);
				else
					i++;
				// printf("after i = %d\n", i);
			}
		}
		tmp = tmp->next;
	}
}