#include "../../minishell.h"

void	clean_str(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			handle_dquotes(s, &i);
		else if (s[i] == '\'')
			handle_squotes(s, &i);
		else
			handle_noquotes(s, &i);
	}
}

void    clean_command(t_list *pipes)
{
	int				i;
	t_list			*tmp;
	t_command		cmd;
	t_list			*tmp_redirs;
	t_redirection	redir;

	(void)pipes;
	while (tmp)
	{
		cmd = *(t_command *)tmp->content;
		tmp_redirs = cmd.redirections;
		while (tmp_redirs)
		{
			clean_str(redir.file_name);
			tmp_redirs = tmp_redirs->next;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (cmd.full_args[i])
		clean_str(cmd.full_args[i++]);
	clean_str(cmd.cmd);
}