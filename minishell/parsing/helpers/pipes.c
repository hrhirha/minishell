#include "../../minishell.h"

void	add_cmd_to_pipes(char *line, t_data *data)
{
	ft_lstadd_back(&data->pipes, ft_lstnew(data->simple_cmd));
	data->i++;
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '|' || line[data->i] == ';' || !line[data->i])
		exit_error(SNTXERR, line[data->i]);
	init_cmd(data);
}
