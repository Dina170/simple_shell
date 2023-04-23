#include "main.h"
void print_tab(char **tab)
{
    int i;

    for (i = 0; tab[i] != NULL; ++i)
    {
        printf("%s\n", tab[i]);
    }
}
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
	size_t n = 0, sargc;
	char *lineptr = NULL, **command;
	ssize_t reads, command_argc, i;
	char  *prompt = "($) ", *delim = " \n";
	char **sargv = NULL;
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
			free(sargv);
			free(lineptr);
			if (!isatty(STDIN_FILENO))
				write(STDOUT_FILENO, prompt, 4);
			return (-1);
		}
		lineptr[reads] = '\0';
		sargv = _strtok(lineptr, delim);
		sargc = 0;
		if (concat_sep(sargv) != -1)
		{
			errorHandler(6 + concat_sep(sargv), in_count, NULL);
			in_count--;
		}
		else
			while (sargv && sargv[sargc])
			{
				for (command_argc = 0; sargv[sargc] && sargv[sargc][0] != ';'; sargc++)
					command_argc++;
				if (command_argc)
				{
					command = malloc(sizeof(char *) * (command_argc + 1));
					for (i = 0; i < command_argc; i++)
						command[i] = sargv[sargc - (command_argc) + i];
					command[i] = NULL;
					exec(command, in_count, env);
					free(command);
				}
				if (sargv[sargc])
					sargc++;
			}
	}
	free(lineptr);
	free(sargv);
	return (0);
}
