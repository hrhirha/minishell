/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:23:59 by hrhirha           #+#    #+#             */
/*   Updated: 2021/02/20 11:25:02 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <signal.h>

# define BUFFER_SIZE 1024

int		get_next_line(int fd, char **line);
void	ft_free(char **s);
int     ft_line_found(char *s);
char	*ft_fill_line(char *s);

#endif
