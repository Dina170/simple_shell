#include "main.h"

void exc(char **argv)
{
	pid_t pid;

	printf("before");

	pid = fork();
	if (pid == -1)
	{
	perror("error fork");
	exit(1);
	}
	else if (pid == 0)
	{
	if (execve(argv[0], argv, NULL) == -1)
	    perror("error exc");
	}
	else
	{
	wait(NULL);
	}
}
