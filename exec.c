#include "main.h"

/**
  * builtin_exec - executes built in commands
  * @argv: array of str of shell commands
  *
  * Return: 0 if command is found, -1 otherwise
  */
char builtin_exec(char **argv)
{
	com_t coms[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"cd", shell_cd}
	};
	int i;

	for (i = 0; i < 3; i++)
	{
		if (!_strncmp(coms[i].command, argv[0], 4))
		{
			coms[i].f(argv);
			return (0);
		}
	}
	return (-1);
}

/**
  * exec - execute programs
  * @argv: array of strings of shell arguments
  * @env: array of str
  */
void exec(char **argv, char **env)
{
	pid_t pid = 0;
	char *command = NULL, *actual_command = NULL;

	if (!builtin_exec(argv))
	{
		return;
	}
	command = argv[0];
	actual_command = find_path(command);
	if (actual_command)
	{
		pid = fork();
	}
	else
	{
		actual_command = command;
	}
	if (pid == -1)
	{
		perror("error fork");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(actual_command, argv, env) == -1)
		{
			perror(program_name);
		}
	}
	else
	{
		wait(NULL);
	}
}
