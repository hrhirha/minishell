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
	char	*tmp;

	tmp = "";
    while (isblank(line[data->i]) == 0)
        data->i++;
    if (line[data->i] == '>' || line[data->i] == '<' ||
        line[data->i] == '|' || line[data->i] == ';' ||
        line[data->i] == '\0')
        exit_error(SNTXERR, line[data->i]);
	else if (line[data->i] == '"')
	{
		tmp = ft_strjoin(tmp, handle_dquotes(line, data));
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
}
