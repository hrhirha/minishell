#include "../../minishell.h"

char	*handle_escape(char *line, t_data *data)
{
	char *sub;

	data->i++;
	sub = ft_substr(line, data->i, 1);
	return (sub);
}