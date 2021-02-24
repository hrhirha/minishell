#include "../../minishell.h"

int		isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}

char	*handle_escape(char *line, t_data *data)
{
	char *sub;

	data->i++;
	sub = ft_substr(line, data->i, 1);
	return (sub);
}
