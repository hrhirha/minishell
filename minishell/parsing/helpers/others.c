#include "../../minishell.h"

char	*handle_escape(char *line, t_data *data)
{
	char *sub;

	data->i++;
	sub = ft_substr(line, data->i, 1);
	return (sub);
}

char	*unquoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 0;
	while ((line[*i + j] != ';' && line[*i + j] != '|' && line[*i + j] &&
			line[*i + j] != ' ') || line[*i + j - 1] == '\\')
		j++;
	substr = ft_substr(line, *i, j);
	*i += j;
	return (substr);
}
