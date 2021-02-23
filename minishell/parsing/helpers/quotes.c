#include "../../minishell.h"

char	*handle_dquotes(char *line, t_data *data)
{
	char	*quoted_str;
	char	*substr;
	char	*tmp;
	int	 j;

	data->i++;
	quoted_str = ft_calloc(1, 1);
	while (line[data->i] != '"' && line[data->i])
	{
		j = 0;
		while (line[data->i + j] != '\\' &&
				line[data->i + j] != '"' && line[data->i + j])
				j++;
		printf("j = %d\n", j);
		substr = ft_substr(line, data->i, j);
		tmp = quoted_str;
		quoted_str = ft_strjoin(quoted_str, substr);
		free(substr);
		free(tmp);
		data->i += j;
		if (line[data->i] == '\\')
		{
			tmp = quoted_str;
			substr = handle_escape(line, data);
			quoted_str = ft_strjoin(quoted_str, substr);
			free(tmp);
			free(substr);
			data->i++;
		}
	}
	return (quoted_str);
}

char	*dquoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 1;
	while (line[*i + j] != '"' && line[*i + j])
		j++;
	substr = ft_substr(line, *i, j + 1);
	if (line[*i + j] == '"')
		*i += j + 1;
	else
		*i += j;
	return (substr);
}

char	*squoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 1;
	while (line[*i + j] != '\'' && line[*i + j])
		j++;
	substr = ft_substr(line, *i, j + 1);
	if (line[*i + j] == '\'')
		*i += j + 1;
	else
		*i += j;
	return (substr);
}