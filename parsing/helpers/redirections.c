/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:55:51 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/17 18:02:05 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		get_filename(char *line, t_data *data)
{
	int	ret;

	ret = 0;
	while (isblank(line[data->i]) == 0)
		data->i++;
	if (line[data->i] == '>' || line[data->i] == '<' || line[data->i] == '|'
		|| line[data->i] == ';' || line[data->i] == '\0')
	{
		ret = error(SNTXERR, line[data->i]);
		g_exist.last_exec = 258;
	}
	data->redirection->file_name = get_str(line, &data->i);
	if (line[data->i] == '|' || line[data->i] == ';'
		|| !line[data->i] || ret == 1)
		get_command_and_args(line, data, ret);
	return (ret);
}

void	get_redir_type(char *line, t_data *data)
{
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
	}
}

int		get_redirection(char *line, t_data *data)
{
	int	ret;

	ret = 0;
	data->redirection = malloc(sizeof(t_redirection));
	if (!data->redirection)
		exit_errno(ENOMEM);
	get_redir_type(line, data);
	ret = get_filename(line, data);
	ft_lstadd_back(&data->simple_cmd->redirections,
				ft_lstnew(data->redirection));
	return (ret);
}
