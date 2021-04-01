/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/18 16:32:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "get_next_line/get_next_line.h"
# include "parsing/errors/errors.h"
# include <sys/wait.h>

# define PROMPT "\033[01;31muser@minishell\033[00m$ "
# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1
# define LEFT_REDIR 1
# define RIGHT_REDIR 2
# define DRIGHT_REDIR 3

struct			s_exist
{
	int			pid;
	int			last_exec;
	int			dir;
	int			quote;
	char		*storage;
}				g_exist;

typedef struct	s_redirection
{
	int		type;
	char	*file_name;
}				t_redirection;

typedef struct	s_command
{
	char	**full_args;
	t_list	*redirections;
}				t_command;

typedef struct	s_minishell
{
	t_list	*cmds;
	char	**env;
	int		out;
	int		in;
}				t_minishell;

typedef struct	s_data
{
	int				i;
	char			*cmd;
	t_minishell		*command;
	t_list			*pipes;
	t_command		*simple_cmd;
	t_redirection	*redirection;
	int				ac;
}				t_data;

typedef struct	s_helper1
{
	t_command	*command;
	int			**pipes_fd;
	int			*forks;
	int			commands_len;
}				t_helper1;

int				parse_line(char *line, t_data *data);
int				get_redirection(char *line, t_data *data);
void			get_command_and_args(char *line, t_data *data, int ret);
int				add_cmd_to_pipes(char *line, t_data *data);
int				add_pipes_to_cmds(char *line, t_data *data);
void			add_last_cmd(char *line, t_data *data);
int				isblank(int c);
int				tab_size(char **t);
void			free_tab(char **t);
void			init_cmd(t_data *data);
char			*get_str(char *line, int *i);
char			*dquoted_str(char *line, int *i);
char			*squoted_str(char *line, int *i);
char			*unquoted_str(char *line, int *i);
void			set_env(char **s, t_data *data);
char			*get_env_value(char *key, char **env);
void			free_data(t_data *data);
void			scan_command(t_list *pipes, char **env);
char			*handle_dquotes(char *s, int *i, char **env);
char			*handle_squotes(char *s, int *i);
char			*handle_noquotes(char *s, int *i, char **env);
void			handle_escape(char *s, int *i, char c, char **str);
void			handle_env_expansion(char *s, int *i, char **env, char **str);
int				split_arg_exp(int i, t_command *cmd);
void			handle_tilde_expansion(char *s, int *i, char **env, char **str);
void			reset_std(t_minishell *minishell);
int				read_file(char *file_name);
int				create_empty_file(char *file_name);
int				create_append_file(char *file_name);
int				commands_loop2(t_minishell *minishell, t_list *my_pipe);
int				loop_redirections2(t_redirection *redirection);
void			func1(int **pipes_fd, int *forks, int commands_len);
void			func2(int i, int **pipes_fd, int commands_len);
int				func3(t_minishell *minishell, t_command *command,
		int **pipes_fd, int *forks);
int				func4(t_minishell *minishell, t_command *command,
		int **pipes_fd, int *forks);
int				func5(int **pipes_fd, int *forks);
int				func6(int **pipes_fd, int *forks, int commands_len);
int				func7(t_minishell *minishell, t_helper1 helper, int i);
int				get_next_line(int fd, char **line);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(const char *s1);
int				ft_strcmp(const char *x, const char *y);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putchar_fd(char c, int fd);
int				ft_isalpha(int c);
char			*trimit(char *s);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
char			**get_paths2(char **paths, char *tmp, char **env, int i);
char			**get_paths(char **env);
char			*found_exec2(char **paths, char *tmp1);
char			*found_exec(t_command *command, t_minishell *minishell);
int				ft_str_has_char(const char *s, int c);
int				env_compair(char *var1, char *var2);
int				vars_counter_and_update(char **new_vars, char **env);
int				var_exist(char *var, char **env);
char			**get_new_env(char **new_vars, char **env, int len);
int				ft_is_equal(int c);
int				arg_has_equal(char *str);
int				ft_is_userscore(int c);
int				arg_start_with_char(char *str);
int				is_valid_arg(char *arg, int show_error);
int				is_valid_arg2(char *arg, int show_error);
int				valid_arg(char *str);
int				count_valid_args(char **args);
char			**set_valid_envs(t_command *command);
void			free_double(char **str);
void			free_double_int(int **str);
void			free_commands(t_minishell *minishell);
int				vars_counter_(char **new_vars, char **env);
int				is_valid_arg2(char *arg, int show_error);
int				count_valid_args2(char **args);
void			display_env_chars(char *env);
int				ex_helper1(char *arg);
void			ex_helper2(char **env);
int				shell_env(t_minishell *minishell);
int				shell_export(t_command *command, t_minishell *minishell);
int				shell_unset(t_command *command, t_minishell *minishell);
int				words_counter(char **env);
char			*found_exec(t_command *command, t_minishell *minishell);
void			echo_display(char **full_args, int index);
void			shell_parce(t_minishell *minishell, char *line);
char			*shell_read(void);
int				shell_execute(t_minishell *minishell, t_command *current);
int				shell_launch(t_minishell *minishell, t_command *command);
int				shell_cd(t_command *command, char **env);
int				shell_exit(t_command *command);
int				shell_echo(t_command *command, t_minishell *minishell);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));
int				loop_redirections(t_minishell *minishell, t_command *command);
int				handle_command(t_minishell *minishell, t_command *command);
int				commands_loop(t_minishell *minishell, t_list *pipe);
int				pipes_loop(t_minishell *minishell);
void			set_pwd_oldpwd(char *new_path, char **env, int type);
int				arg_exist(char *arg, t_minishell *minishell);
void			export_varible(char *arg, t_minishell *minishell);
void			unset_varible(char *arg, t_minishell *minishell);
void			export_varible_edit(char *arg, t_minishell *minishell);
int				export_arg_exist(char *full_arg, t_minishell *minishell);
int				shell_pwd(t_minishell *minishell);
int				export_env_compair(char *var1, char *var2);
void			export_invalid_arg_msg(char *arg);
int				valid_arg_export(char *str);
char			*env_value(char *arg);
char			**copy_env(char **env, int len);
void			display_env_ordred2(char **env, int count);
int				display_env_ordred(char **env);
void			unset_invalid_arg_msg(char *arg);
void			check_lower_case(t_command *command);
void			update_env_pwd(t_data *data);
#endif
