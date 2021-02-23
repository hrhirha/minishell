/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 12:10:16 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/21 12:10:36 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
#include "parsing/errors/errors.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <stdio.h>

# define BUFFER_SIZE 1024

# define RIGHT_REDIR 1
# define DRIGHT_REDIR 2
# define LEFT_REDIR 3

typedef struct	s_redirection
{
	int				type;		   // 1 = > , 2 = >>, 3 = <
	char			*file_name;
}				t_redirection;

typedef struct	s_command
{
	char			*cmd;			// "echo aaaa	 bbbb" // don't include -n
	char			*exec;			// "echo"
	char			**args;			// ["aaaa", "bbbb"]
	char			**full_args;	// ["echo", "aaaa", "bbbb"]
	int				option;			// 1 if echo -n, 0 if not
	t_list			*redirections;
}				t_command;

// typedef struct	s_pipeline
// {
// 	int				pipe_count;
// 	t_command		*commands;
// }				t_pipeline;

typedef struct	s_minishell // ;
{
	// t_pipeline		*pipes;
	t_list			*cmds;
	char			**env;
}				t_minishell;

typedef struct	s_data
{
	int				i;
	// char			**env;
	t_minishell		*command;
	t_list			*pipes;
	t_command		*simple_cmd;
	t_redirection	*redirection;
	// t_list			*cmds;
	// t_pipeline		*pipeline;
	// t_list			*redirections;
}				t_data;

/*
** parsing
*/
void			parse_line(char *line, t_data *data);

/*
** redirections
*/
void			get_redirection(char *line, t_data *data);

/*
** helpers
*/
int				isblank(int c);
char			*handle_dquotes(char *line, t_data *data);
char			*dquoted_str(char *line, int *i);
char			*squoted_str(char *line, int *i);
char			*unquoted_str(char *line, int *i);
char			*handle_escape(char *line, t_data *data);

#endif
