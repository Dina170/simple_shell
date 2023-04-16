#include "main.h"

/**
  * exec - execute programs
  * @argv: array of strings of shell arguments
  * @program_name: invocation name
  * @env: array of str
  */
void exec(char **argv, char *program_name, char **env)
{
	pid_t pid;
	char *command = NULL, *actual_command = NULL;

	command = argv[0];
	actual_command = find_path(command);

	pid = fork();
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
			_exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
}
