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
# include "parsing/errors/errors.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <stdio.h>

# define PROMPT "user@minishell$ "

# define BUFFER_SIZE 1024

# define RIGHT_REDIR 1
# define DRIGHT_REDIR 2
# define LEFT_REDIR 3

typedef struct	s_redirection
{
	int				type;
	char			*file_name;
}				t_redirection;

typedef struct	s_command
{
	char			**full_args;
	t_list			*redirections;
}				t_command;

typedef struct	s_minishell
{
	t_list			*cmds;
	char			**env;
}				t_minishell;

typedef struct	s_data
{
	int				i;
	char			**env;
	char			*cmd;
	t_minishell		*command;
	t_list			*pipes;
	t_command		*simple_cmd;
	t_redirection	*redirection;
	int				ac;
}				t_data;

/*
** parsing
*/
int				parse_line(char *line, t_data *data);

/*
** commandParsing
*/
int				get_redirection(char *line, t_data *data);
void			get_command_and_args(char *line, t_data *data, int ret);
int				add_cmd_to_pipes(char *line, t_data *data);
int				add_pipes_to_cmds(char *line, t_data *data);
void			add_last_cmd(char *line, t_data *data);

/*
** helpers
*/
int				isblank(int c);
void			init_cmd(t_data *data);

char			*get_str(char *line, int *i);
char			*dquoted_str(char *line, int *i);
char			*squoted_str(char *line, int *i);
char			*unquoted_str(char *line, int *i);

void			set_env(char **s, t_data *data);

void			free_data(t_data *data);

/*
** special chars `"`, `'`, `\`, `$`
*/
void			scan_command(t_list *pipes, char **env);
char			*handle_dquotes(char *s, int *i, char **env);
char			*handle_squotes(char *s, int *i);
char			*handle_noquotes(char *s, int *i, char **env);
void			handle_escape(char *s, int *i, char c, char **str);
void			handle_env_expansion(char *s, int *i, char **env, char **str);
void			handle_tilde_expansion(char *s, int *i, char **env, char **str);

#endif
