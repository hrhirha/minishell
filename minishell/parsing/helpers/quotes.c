#include "../../minishell.h"

char	*handle_dquotes(char *line, t_data *data)
{
	char	*quoted_str;
	char	*substr;
	int	 j;

	data->i++;
	quoted_str = ft_calloc(1, 1);
	while (line[data->i] != '"' && line[data->i])
	{
		j = 0;
		while (line[data->i + j] != '\\' &&
				line[data->i + j] != '"' && line[data->i + j])
				j++;
		substr = ft_substr(line, data->i, j);
		quoted_str = ft_strjoin(quoted_str, substr);
		data->i += j;
		if (line[data->i] == '\\')
		{
			substr = handle_escape(line, data);
			quoted_str = ft_strjoin(quoted_str, substr);
			data->i++;
		}
	}
	return (quoted_str);
}
