#include "../../minishell.h"

int		isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}

void	init_cmd(t_data *data)
{
	if (!(data->simple_cmd = malloc(sizeof(t_command))))
		exit_errno(ENOMEM);
	if (!(data->simple_cmd->cmd = ft_calloc(1, 1)))
		exit_errno(ENOMEM);
	data->simple_cmd->redirections = NULL;
	data->ac = 0;
}

char	*handle_escape(char *line, t_data *data)
{
	char *sub;

	data->i++;
	sub = ft_substr(line, data->i, 1);
	return (sub);
}
