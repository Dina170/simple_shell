#include "main.h"

/**
  * shell_input - gets shell input
  * @lineptr: pointer to the input string
  * @n: size of input buffer
  * @aliases: array of aliases
  */
void shell_input(char **lineptr, size_t *n, char **aliases)
{
	ssize_t reads = getline(lineptr, n, stdin);

	if (reads == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(*lineptr);
		free_array(aliases);
		exit(0);
	}
	(*lineptr)[reads] = '\0';
}

/**
  * m_helper - handle shell input for execution
  * @sargv: array of arguments
  * @inCnt: shell input counter
  * @extStat: exit state
  * @aliases: array of aliases
  * @env: array of str
  *
  * Return: 0 if success, 1 if it fails
  */
char m_helper(char **sargv, unsigned long *inCnt, size_t *extStat,
		char **aliases,  char **env)
{
	size_t sargc = 0, command_argc, i;
	char **command, last_state = 1, execute_case = 1, is_and = 1;

	if (concat_sep(sargv) != -1)
		errorHandler(6 + concat_sep(sargv), *inCnt, NULL), (*inCnt)--;
	else
		while (sargv && sargv[sargc])
		{
			for (command_argc = 0; sargv[sargc] && sargv[sargc][0] != ';'
					&& sargv[sargc][0] != '&' && sargv[sargc][0] != '|'; sargc++)
				command_argc++;
			if (command_argc)
			{
				command = malloc(sizeof(char *) * (command_argc + 1));
				if (!command)
				{
					return (1);
				}
				for (i = 0; i < command_argc; i++)
					command[i] = sargv[sargc - (command_argc) + i];
				command[i] = NULL;
				command = getalias(command, command_argc, aliases);
				if (!command)
					return (1);
				if (execute_case)
				{
					*extStat = exec(command, *inCnt, aliases, env);
					last_state = (!*extStat) ? 1 : 0;
				}
				else
					last_state = (is_and) ? 0 : 1;
				if (sargv[sargc] && sargv[sargc][0] == '&')
					is_and = 1, execute_case = last_state;
				else if (sargv[sargc] && sargv[sargc][0] == '|')
					is_and = 0, execute_case = (last_state) ? 0 : 1;
			}
			if (sargv[sargc])
				sargc++;
		}
	return (0);
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
	size_t n = 0, exit_status;
	char *lineptr = NULL, **sargv = NULL;
	char  *prompt = "$ ", *delim = " \n";
	unsigned long in_count = 0;
	char **aliases = malloc(sizeof(char *) * 1024);

	(void) argv;
	aliases[0] = NULL;
	signal(SIGINT, handle_sigint);
	while (1 && argc == 1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		shell_input(&lineptr, &n, aliases);
		in_count++;
		sargv = _strtok(lineptr, delim);
		if (m_helper(sargv, &in_count, &exit_status, aliases, env))
			return (1);
		free_array(sargv);
	}
	free(lineptr);
	free_array(aliases);
	return (0);
}
