#include "main.h"

/**
 * shell_exit - exits the shell
 * @args: array of str of shell arguments
 * @in_count: shell input counter
 *
 * Return: exit status
 */
size_t shell_exit(char **args, unsigned long in_count)
{
	if (args[1])
	{
		char arg_status;
		int status = _atoi(args[1], &arg_status);

		if (!arg_status && status >= 0)
			exit(status);
		else
		{
			errorHandler(0, in_count, args[1]);
		}
	}
	else
	{
		exit(0);
	}
	return (2);
}


/**
 * shell_env - prints environment
 * @args: array of str of shell arguments
 * @in_count: shell input counter
 *
 * Return: exit status
 */
size_t shell_env(char **args, unsigned long in_count)
{
	int i;

	(void) args, (void) in_count;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * _setenv - updates or adds an environmental variable
 * @args: array of arguments passed to the shell
 * @in_count: shell input counter
 *
 * Return: exit status
 */
size_t _setenv(char **args, unsigned long in_count)
{
	size_t size, i = 0;
	int index, len;
	char *new_value;

	if (!args[1] || !args[2])
	{
		errorHandler(2, in_count, NULL);
		return (2);
	}
	while (args[1][i])
	{
		if (args[1][i] == '=')
		{
			errorHandler(3, in_count, args[1]);
			return (2);
		}
		i++;
	}
	new_value = malloc(_strlen(args[1]) + _strlen(args[2]) + 2);
	if (!new_value)
		return (2);
	_strcpy(new_value, args[1]);
	_strcat(new_value, "=");
	_strcat(new_value, args[2]);
	len = _strlen(args[1]) + 1;
	if (_getenv(args[1]))
		for (index = 0; environ[index]; index++)
			if (_strncmp(new_value, environ[index], len) == 0)
			{
				environ[index] = new_value;
				return (0);
			}
	for (size = 0; environ[size]; size++)
		;
	environ[size] = new_value;
	environ[size + 1] = NULL;
	return (0);
}
/**
 * _unsetenv - deletes an environmental variable
 * @args: array of arguments passed to the shell
 * @in_count: shell input counter
 *
 * Return: exit status
 */
size_t _unsetenv(char **args, unsigned long in_count)
{
	char *var_equal;
	size_t size, i = 0;
	int index, index2, len;

	if (!args[1])
	{
		errorHandler(4, in_count, NULL);
		return (2);
	}
	while (args[1][i])
	{
		if (args[1][i] == '=')
		{
			errorHandler(5, in_count, args[1]);
			return (2);
		}
		i++;
	}
	if (!_getenv(args[1]))
		return (0);
	var_equal = malloc(_strlen(args[1]) + 2);
	if (!var_equal)
		return (2);
	_strcpy(var_equal, args[1]);
	_strcat(var_equal, "=");
	len = _strlen(args[1]) + 1;
	for (size = 0; environ[size]; size++)
		;
	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (_strncmp(var_equal, environ[index], len) == 0)
		{
			free(environ[index]);
			continue;
		}
		environ[index2] = environ[index];
		index2++;
	}
	environ[size - 1] = NULL, free(var_equal);
	return (0);
}

/**
 * shell_cd - changes directory to arg
 * @args: the directory to change to or nothing
 * @in_count: shell input counter
 *
 * Return: exit status
 */
size_t shell_cd(char **args, unsigned long in_count)
{
	char current_dir[PATH_MAX], prev_dir[PATH_MAX];
	char *setenv_args[3];

	if (args[1] == NULL)
	{
		getcwd(current_dir, PATH_MAX);
		setenv_args[0] = "setenv", setenv_args[1] = "OLDPWD";
		setenv_args[2] = current_dir, _setenv(setenv_args, in_count);
		chdir(_getenv("HOME"));
	}
	else if (_strncmp(args[1], "-", 1) == 0)
	{
		if (_getenv("OLDPWD"))
		{
			getcwd(prev_dir, PATH_MAX);
			chdir(_getenv("OLDPWD")), getcwd(current_dir, PATH_MAX);
			write(STDOUT_FILENO, current_dir, _strlen(current_dir));
			write(STDOUT_FILENO, "\n", 1);
			setenv_args[0] = "setenv", setenv_args[1] = "OLDPWD";
			setenv_args[2] = prev_dir, _setenv(setenv_args, in_count);
		}
	}
	else
	{
		getcwd(current_dir, PATH_MAX);
		setenv_args[0] = "setenv", setenv_args[1] = "OLDPWD";
		setenv_args[2] = current_dir, _setenv(setenv_args, in_count);
		if (chdir(args[1]) != 0)
		{
			errorHandler(1, in_count, args[1]);
			return (2);
		}
	}
	getcwd(current_dir, PATH_MAX);
	setenv_args[0] = "setenv", setenv_args[1] = "PWD";
	setenv_args[2] = current_dir, _setenv(setenv_args, in_count);
	return (0);
}
