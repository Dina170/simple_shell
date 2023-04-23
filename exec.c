#include "main.h"

/**
  * builtin_exec - executes built in commands
  * @argv: array of str of shell commands
  * @in_count: shell input counter
  *
  * Return: 0 if command is found, -1 otherwise
  */
char builtin_exec(char **argv, unsigned long in_count)
{
	com_t coms[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"cd", shell_cd},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv}
	};
	int i;

	if (!_strncmp("env", argv[0], 3) && argv[1])
		return (-1);
	for (i = 0; i < 5; i++)
	{
		if (!_strncmp(coms[i].command, argv[0], 8))
		{
			coms[i].f(argv, in_count);
			return (0);
		}
	}
	return (-1);
}

/**
  * exec - execute programs
  * @argv: array of strings of shell arguments
  * @in_count: shell input counter
  * @env: array of str
  */
void exec(char **argv, unsigned long in_count, char **env)
{
	pid_t pid = 0;
	char *command = NULL, *actual_command = NULL;

	if (!builtin_exec(argv, in_count))
		return;
	command = argv[0];
	actual_command = find_path(command);
	if (actual_command)
		pid = fork();
	else
		actual_command = command;
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(actual_command, argv, env) == -1)
		{
			errorHandler(8, in_count, argv[0]);
		}
	}
	else
	{
		wait(NULL);
	}
}
