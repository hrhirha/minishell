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
			sub = handle_squotes(s, &i);
		else
			sub = handle_noquotes(s, &i, env);
		tmp = scaned_str;
		scaned_str = ft_strjoin(scaned_str, sub);
		free(tmp);
		free(sub);
	}
	printf("\tscaned_str = `%s`\n", scaned_str);
}

void	scan_redirs(t_list *redirs, char **env)
{
	t_redirection	redir;

	while (redirs)
	{
		redir = *(t_redirection *)redirs->content;
		printf("[%d]", redir.type);
		scan_str(redir.file_name, env);
		redirs = redirs->next;
	}
}

void    scan_command(t_list *pipes, char **env)
{
	int				i;
	t_list			*tmp;
	t_command		cmd;
	t_list			*tmp_redirs;

	tmp = pipes;
	while (tmp)
	{
		cmd = *(t_command *)tmp->content;
		tmp_redirs = cmd.redirections;
		printf("redirs:\n");
		scan_redirs(tmp_redirs, env);
		printf("\n");
		tmp = tmp->next;
		printf("command: \n");
		scan_str(cmd.cmd, env);
		i = 0;
		printf("arguments: \n");
		if (cmd.full_args)
		{
			while (cmd.full_args[i])
				scan_str(cmd.full_args[i++], env);
		}
		printf("\n");
	}
}