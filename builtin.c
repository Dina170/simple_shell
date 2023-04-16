#include "main.h"
/**
 * shell_exit - exits the shell
 * Return: void
 */

void shell_exit(char **args)
{
	exit(0);
}


/**
 * shell_env - prints environment
 * Return: void
 */

void shell_env(char **args)
{
	int i;

	(void) args;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * shell_cd - changes directory to arg
 * @ard: the directory to change to or nothing
 */

void shell_cd(char **arg)
{
	int i = 0;
	char *homeval = NULL, *home = NULL;

	if (arg[1] == NULL)
		homeval = _getenv("HOME");
	else
		homeval = ar[1]; 
	chdir(homeval);
}
