#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

// gcc -Wall -Werror -Wextra timel.c -o timel

int main(int ac, char **av)
{
	extern char		**environ;
	struct rusage	usage;
	pid_t			child_process;
	int				status = 0;

	if (ac == 2)
	{
		child_process = fork();
		av++;
		if (child_process == 0)
			execve(av[0], av, environ);
		waitpid(child_process, &status, 0);
		getrusage(RUSAGE_CHILDREN, &usage);
		fprintf(stderr, "time: %5ld page reclaims\n", usage.ru_minflt);
	}
	else
		fprintf(stderr, "Only one argument\n");
	return 0;
}