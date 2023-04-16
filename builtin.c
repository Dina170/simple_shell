#include "main.h"

/**
 * shell_exit - exits the shell
 * @args: array of str of shell arguments
 */
void shell_exit(char **args)
{
	if (args[1])
	{
		char arg_status;

		int status = _atoi(args[1], &arg_status);
		if (!arg_status && status >= 0)
			exit(status);
		else
		{
			char buf[100];
			size_t len = 23 + _strlen(program_name)
				+ _strlen(my_itoa(in_count, buf, 10))
				+ _strlen(args[0])
				+ _strlen(args[1]);
			char *error_msg = malloc(len);
			_strcpy(error_msg, program_name);
			_strcat(error_msg, ": ");
			_strcat(error_msg, buf);
			_strcat(error_msg, ": ");
			_strcat(error_msg, args[0]);
			_strcat(error_msg, ": Illegal number: ");
			_strcat(error_msg, args[1]);
			_strcat(error_msg, "\n");
			write(STDOUT_FILENO, error_msg, len);
			free(error_msg);
		}
	}
	else
	{
		exit(0);
	}
}


/**
 * shell_env - prints environment
 * @args: array of str of shell arguments
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
 * @arg: the directory to change to or nothing
 */
void shell_cd(char **arg)
{
	char *homeval = NULL;

	if (arg[1] == NULL)
		homeval = _getenv("HOME");
	else
		homeval = arg[1];
	chdir(homeval);
}
