#ifndef GNL_TERM_H
# define GNL_TERM_H
# include "../minishell.h"

int		putchar_tc(int c);
void	backspace(char **line);
void	up_key(char **line);
void	down_key(char **line);
void	handle_keys(char **line, long c);
int     gnl_term(char **line);
void	get_printable(char **line, long c);
void	setup_term();

#endif
