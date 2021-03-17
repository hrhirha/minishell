# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/29 16:30:24 by ler-rech          #+#    #+#              #
#    Updated: 2021/03/17 17:33:33 by ler-rech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
GCC = gcc
FILES_C =	main.c \
			main2.c \
			main3.c \
			main4.c \
			main5.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			src/functions.c \
			src/exe.c \
			src/exe2.c \
			src/cd.c \
			src/exit.c \
			src/echo.c \
			src/helper.c \
			src/env.c \
			src/export.c \
			src/unset.c \
			src/pwd.c \
			src/free.c \
			parsing/*.c \
			parsing/errors/*.c \
			parsing/helpers/*.c \
			parsing/spec_chars/*.c

# FILES_O =	test.o main.o src/exe.o src/functions.o cd.o exit.o echo.o helper.o env.o export.o unset.o free.o data.o
FILES_O =	*.o

NAME = minishell

FILE_H = libft.h

all: lib $(NAME)

lib:
	cd libft; make ; make bonus

$(NAME):
	@$(GCC) -o minishell $(FILES_C) libft/libft.a

san:
	@$(GCC) -o minishell $(FILES_C) libft/libft.a -fsanitize=address -g

clean:
	cd libft; make clean

fclean: clean
	rm -rf minishell; 
	cd libft; make fclean

re: fclean all

bonus: all

test:
	@rm -rf minishell
	@$(GCC) -o minishell $(FILES_C) libft/libft.a
	@./minishell
