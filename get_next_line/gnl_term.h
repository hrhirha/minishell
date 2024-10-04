/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_term.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:14:34 by hrhirha           #+#    #+#             */
/*   Updated: 2021/04/09 11:14:36 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_TERM_H
# define GNL_TERM_H
# include "../minishell.h"

int		gnl_term(void);
void	setup_term(void);
void	get_printable(long c);
int		putchar_tc(int c);
void	backspace(void);
void	handle_keys(long c);
void	ft_free(char **s);
void	signals(int sig);
void	add_hist(char *s);
void	up_hist(void);
void	down_hist(void);

#endif
