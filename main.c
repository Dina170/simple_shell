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
	size_t n = 0;
	char *lineptr = NULL;
	ssize_t reads;
	char  *prompt = "($) ", *delim = " \n";
	char **sargv;

	while (1 && argc == 1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 4);
		reads = getline(&lineptr, &n, stdin);
		if (reads == -1)
		{
			if (!isatty(STDIN_FILENO))
				write(STDOUT_FILENO, prompt, 4);
			return (-1);
		}
		sargv = _strtok(lineptr, delim);
		if (sargv)
			exec(sargv, argv[0], env);
	}
	free(sargv);
	free(lineptr);
	return (0);
}
