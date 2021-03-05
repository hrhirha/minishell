/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:55:51 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/05 18:40:41 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_filename(char *line, t_data *data)
{
	int	ret;

	ret = 0;
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '>' || line[data->i] == '<' || line[data->i] == '|'
		|| line[data->i] == ';' || line[data->i] == '\0')
	{
		ret = error(SNTXERR, line[data->i]);
	}
	data->redirection->file_name = get_str(line, &data->i);
	if (line[data->i] == '|' || line[data->i] == ';'
		|| !line[data->i] || ret == 1)
		get_command_and_args(line, data, ret);
	return (ret);
}

int	get_redirection(char *line, t_data *data)
{
	int	ret;

	ret = 0;
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
			return (error(SNTXERR, line[data->i]));
	}
	if (get_filename(line, data) == 1)
		ret = 1;
	ft_lstadd_back(&data->simple_cmd->redirections,
				ft_lstnew(data->redirection));
	return (ret);
}
