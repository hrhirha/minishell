#include "../../minishell.h"

void	scan_str(char *s, char **env)
{
	int		i;
	char	*scaned_str;
	char	*sub;
	char	*tmp;

	scaned_str = ft_calloc(1, 1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			sub = handle_dquotes(s, &i, env);
		else if (s[i] == '\'')
			;// sub = handle_squotes(s, &i);
		else
			;// sub = handle_noquotes(s, &i, env);
		tmp = scaned_str;
		scaned_str = ft_strjoin(scaned_str, sub);
		free(tmp);
		free(sub);
		printf("scaned_str = `%s`\n", scaned_str);
	}
}

void    scan_command(t_list *pipes, char **env)
{
	int				i;
	t_list			*tmp;
	t_command		cmd;
	t_list			*tmp_redirs;
	t_redirection	redir;

	tmp = pipes;
	while (tmp)
	{
		cmd = *(t_command *)tmp->content;
		tmp_redirs = cmd.redirections;
		while (tmp_redirs)
		{
			redir = *(t_redirection *)tmp_redirs->content;
			printf("file\n");
			scan_str(redir.file_name, env);
			tmp_redirs = tmp_redirs->next;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (cmd.full_args[i])
		scan_str(cmd.full_args[i++], env);
	printf("cmd\n");
	scan_str(cmd.cmd, env);
}