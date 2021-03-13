/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/20 17:46:08 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_command(t_command *command)
// {
// 	t_list			*redirs;
// 	t_redirection	redir;
// 	int				j;

// 	redirs = command->redirections;
// 	while (redirs)
// 	{
// 		redir = *(t_redirection *)redirs->content;
// 		printf("[%d]file = `%s`\n", redir.type, redir.file_name);
// 		redirs = redirs->next;
// 	}
// 	if (command->full_args)
// 	{
// 		j = 0;
// 		if (ft_strcmp(command->full_args[j], "cat") == 0)
// 		{
// 			int pid;
// 			if ((pid = fork()) == 0)
// 				execve(ft_strjoin("/bin/", command->full_args[j]), command->full_args, NULL);
// 			else if (pid > 0)
// 				waitpid(pid, &g_last_exec, 0);
// 		}
// 		else if (ft_strcmp(command->full_args[j], "exit") == 0)
// 			exit(0);
// 		while (command->full_args[j])
// 		{
// 			printf("\targ[%d] = `%s`\n", j, command->full_args[j]);
// 			j++;
// 		}
// 	}
// }

// void	test(t_minishell *command)
// {
// 	t_list		*cmds;
// 	t_list		*pipes;
// 	t_command	*cmd;

// 	cmds = command->cmds;
// 	while (cmds)
// 	{
// 		pipes = cmds->content;
// 		scan_command(pipes, command->env);
// 		while (pipes)
// 		{
// 			cmd = (t_command *)pipes->content;
// 			exec_command(cmd);
// 			pipes = pipes->next;
// 		}
// 		cmds = cmds->next;
// 	}
// }

void	ft_getline(char **line, t_data *data)
{
	int parsing_ret;

	data->i = 0;
	write(1, PROMPT, ft_strlen(PROMPT));
	get_next_line(0, line);
	parsing_ret = parse_line(*line, data);
	if (parsing_ret == 0)
		;// test(data->command);
	free_data(data);
}

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		write(1, PROMPT, ft_strlen(PROMPT));
	}
	if (sig == SIGQUIT)
	{
		// ft_putstr_fd("Quit: 3\n", 1);
	}
}

int		main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		exit_errno(ENOMEM);
	data->command = malloc(sizeof(t_minishell));
	if (!data->command)
		exit_errno(ENOMEM);
	set_env(env, data);
	signal(SIGINT, signals);
	signal(SIGQUIT, signals);
	while (1)
	{
		ft_getline(&line, data);
		free(line);
	}
	free_tab(data->command->env);
	free(data->command);
	free(data);
}
