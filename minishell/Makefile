NAME = minishell
CC = gcc -Wall -Wextra -Werror #-fsanitize=address
#CC = gcc -Wall -Wextra -Werror -fsanitize=address

SRCS = minishell.c \
	   get_next_line/*.c \
	   parsing/*.c \
	   parsing/errors/*.c \
	   parsing/helpers/*.c

OBJS = *.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	make bonus -C libft/
	mv libft/libft.a .
	$(CC) $(OBJS) libft.a -o $(NAME)
$(OBJS): $(SRCS)
	$(CC) -c $^

clean:
	make clean -C libft/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf libft.a

re: fclean $(NAME)

compile: $(OBJS)

