# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/29 16:30:24 by ler-rech          #+#    #+#              #
#    Updated: 2021/03/18 17:05:56 by ler-rech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
GCC = gcc $(FLAGS)
FILES_C =	main.c \
			main2.c \
			main3.c \
			main4.c \
			main5.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			src/*.c \
			parsing/*.c \
			parsing/errors/*.c \
			parsing/helpers/*.c \
			parsing/spec_chars/*.c

FILES_O =	*.o

NAME = minishell

FILE_H = libft.h

all: lib $(NAME)

lib:
	make -C libft/
	make bonus -C libft/

$(NAME):
	@$(GCC) -o minishell $(FILES_C) libft/libft.a

san:
	@$(GCC) -o minishell $(FILES_C) libft/libft.a -fsanitize=address

clean:
	make clean -C libft/

fclean: clean
	rm -rf minishell
	make fclean -C libft/

norm:
	@norminette *.c *.h */*.c */*.h */*/*.c */*/*.h

re: fclean all
