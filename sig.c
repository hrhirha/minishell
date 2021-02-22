#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigquit(int sig)
{
	printf("Caught Signal %d\n", sig);
}

int	main()
{
	char buf[10];
	dup2(1, 3);
	write(3, "File descriptor 3", 30);
	write(3, "\n", 1);
	signal(SIGQUIT, handle_sigquit);
	while (1){
		write(1, "waiting: ", 10);
		read(0, buf, 10);
	}
}
