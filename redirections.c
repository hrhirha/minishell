#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#define LEFT	1
#define	RIGHT	2
#define	DLEFT	3
#define	DRIGHT	4

typedef struct	s_red
{
	int		type;
	char	*file;
}				t_red;

void	get_right_redirect(char *s, int *i, t_list **rlist)
{
	t_red	*red;
	int		j;

	*i += 1;
	red = malloc(sizeof(t_red *)); // unprotected
	red->type = RIGHT;
	j = 0;
	while (s[*i] == ' ')
		*i += 1;
	while (s[*i + j] != '>' && s[*i + j] != '<' && s[*i + j] != ' ' && s[*i + j])
	{
		//printf("Right Redirection c= %c\n", s[i + j]);
		j++;
	}
	red->file = ft_substr(s, *i, j);
	//printf("type = %d, file = %s\n", red->type, red->file);
	ft_lstadd_back(rlist, ft_lstnew(red));
	*i += j;
}

void	get_dright_redirect(char *s, int *i, t_list **rlist)
{
	t_red	*red;
	int		j;

	*i += 2;;
	red = malloc(sizeof(t_red *)); // unprotected
	red->type = DRIGHT;
	j = 0;
	while (s[*i] == ' ')
		*i += 1;
	while (s[*i + j] != '>' && s[*i + j] != '<' && s[*i + j] != ' ' && s[*i + j])
		j++;
	red->file = ft_substr(s, *i, j);
	//printf("type = %d, file = %s\n", red->type, red->file);
	ft_lstadd_back(rlist, ft_lstnew(red));
	*i += j;
}

void	get_left_redirect(char *s, int *i, t_list **rlist)
{
	t_red	*red;
	int		j;

	*i += 1;
	red = malloc(sizeof(t_red *)); // unprotected
	red->type = LEFT;
	j = 0;
	while (s[*i] == ' ')
		*i += 1;
	while (s[*i + j] != '<' && s[*i + j] != '>' && s[*i + j] != ' ' && s[*i + j])
	{
		//printf("Right Redirection c= %c\n", s[i + j]);
		j++;
	}
	red->file = ft_substr(s, *i, j);
	//printf("type = %d, file = %s\n", red->type, red->file);
	ft_lstadd_back(rlist, ft_lstnew(red));
	*i += j;
}

void	get_dleft_redirect(char *s, int *i, t_list **rlist)
{
	t_red	*red;
	int		j;

	*i += 2;;
	red = malloc(sizeof(t_red *)); // unprotected
	red->type = DLEFT;
	j = 0;
	while (s[*i] == ' ')
		*i += 1;
	while (s[*i + j] != '<' && s[*i + j] != '>' && s[*i + j] != ' ' && s[*i + j])
		j++;
	red->file = ft_substr(s, *i, j);
	//printf("type = %d, file = %s\n", red->type, red->file);
	ft_lstadd_back(rlist, ft_lstnew(red));
	*i += j;
}

void	get_redirections(char *s, t_list **rlist, char **cmd)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] != '>')
			get_right_redirect(s, &i, rlist);
		else if (s[i] == '>' && s[i + 1] == '>')
			get_dright_redirect(s, &i, rlist);
		else if (s[i] == '<' && s[i + 1] != '<')
			get_left_redirect(s, &i, rlist);
		else if (s[i] == '<' && s[i + 1] == '<')
			get_dleft_redirect(s, &i, rlist);
		else
		{
			j = 0;
			while (s[i] == ' ')
				i++;
			while (s[i + j] != '>' && s[i + j] != '<' && s[i + j])
				j++;
			*cmd = ft_strjoin(*cmd, ft_substr(s, i, j));
			i += j;
		}
	}
}

void	open_files(t_list *rlist)
{
	int		fd;
	t_red	red;
	t_list	*tmp;

	tmp = rlist;
	while (tmp->next)
	{
		red = *(t_red *)tmp->content;
		if (red.type == RIGHT)
			fd = open(red.file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		else if (red.type == DRIGHT)
			fd = open(red.file, O_WRONLY|O_CREAT|O_APPEND, 0644);
		else if (red.type == LEFT)
			fd = open(red.file, O_RDONLY, 0644);
		close(fd);
		tmp = tmp->next;
	}
	/* Open last file */
	red = *(t_red *)tmp->content;
	if (red.type == LEFT)
	{
		fd = open(red.file, O_RDONLY, 0644);
		dup2(fd, 0);
	}
	else
	{
		if (red.type == RIGHT)
			fd = open(red.file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		else if (red.type == DRIGHT)
			fd = open(red.file, O_WRONLY|O_CREAT|O_APPEND, 0644);
		dup2(fd, 1);
	}
}

void	exec_cmd(char *s, ...);

int		main(int ac, char **av)
{
	t_list	*rlist;
	char	*cmd;

	if (ac == 2)
	{
		cmd = "";
		rlist = NULL;
		get_redirections(av[1], &rlist, &cmd);
		if (rlist)
		{
			open_files(rlist);
		}
		if (fork() == 0)
		{
			char **cmdtab = ft_split(cmd, ' ');
			execve(ft_strjoin("/bin/", cmdtab[0]), cmdtab, NULL);
		}
		else
			wait(NULL);
	}
	else
		printf("Wrong arg count\n");
}
