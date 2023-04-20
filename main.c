#include "main.h"

/**
  * main - launch the shell
  * @argc: number of arguments
  * @argv: array of arguments
  * @env: array of str
  *
  * Return: 0
  */
int main(int argc, char *argv[], char *env[])
{
	size_t n = 0, i;
	char *lineptr = NULL;
	ssize_t reads;
	char  *prompt = "($) ", *delim = " \n";
	char **sargv;
	unsigned long in_count = 0;

	(void) argv;

	while (1 && argc == 1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 4);
		reads = getline(&lineptr, &n, stdin);
		in_count++;
		if (reads == -1)
		{
			if (!isatty(STDIN_FILENO))
				write(STDOUT_FILENO, prompt, 4);
			return (-1);
		}
		sargv = _strtok(lineptr, delim);
		if (sargv)
			exec(sargv, in_count, env);
	}
	free(sargv);
	free(lineptr);
	return (0);
}
