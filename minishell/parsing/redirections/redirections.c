/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:55:51 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/21 17:55:52 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    get_filename(char *line, t_data *data)
{
	char	*substr;
	char	*tmp;

	tmp = ft_calloc(1, 1);
    while (isblank(line[data->i]) == 0)
        data->i++;
    if (line[data->i] == '>' || line[data->i] == '<' ||
        line[data->i] == '|' || line[data->i] == ';' ||
        line[data->i] == '\0')
        exit_error(SNTXERR, line[data->i]);
	while (line[data->i] != ';' && line[data->i] != '|' &&
			line[data->i] != ' ' && line[data->i])
	{
		if (line[data->i] == '"')
		{
			substr = dquoted_str(line, &data->i);
			tmp = ft_strjoin(tmp, substr);
		}
		else if (line[data->i] == '\'')
		{
			substr = squoted_str(line, &data->i);
			tmp = ft_strjoin(tmp, substr);
		}
		else
		{
			substr = unquoted_str(line, &data->i);
			tmp = ft_strjoin(tmp, substr);
		}
	}
    data->redirection->file_name = tmp;
	printf("filename = %s\n", tmp);
}

void	get_redirection(char *line, t_data *data)
{
	if (!(data->redirection = malloc(sizeof(t_redirection))))
		exit_errno(ENOMEM);
	if (line[data->i] == '>')
	{
		data->redirection->type = RIGHT_REDIR;
		data->i++;
		if (line[data->i] == '>')
		{
			data->redirection->type = DRIGHT_REDIR;
			data->i++;
		}
	}
	else if (line[data->i] == '<')
	{
		data->redirection->type = LEFT_REDIR;
		data->i++;
		if (line[data->i] == '<')
			exit_error(SNTXERR, line[data->i]);
	}
    get_filename(line, data);
	ft_lstadd_back(&data->simple_cmd->redirections,
				ft_lstnew(data->redirection));
	// t_redirection redir;
	// redir = *(t_redirection *)data->simple_cmd->redirections->content;
	// printf("filename = %s\n", redir.);
}
