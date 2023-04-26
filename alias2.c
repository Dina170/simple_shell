#include "main.h"

/**
  * setalias - define an alias
  * @arg: alias arg
  * @aliases: array of aliases
  * @len: index of '='
  *
  * Return: 0 if success, 1 if it fails
  */
char setalias(char *arg, char **aliases, size_t len)
{
	int index;
	size_t size;
	char *alias;

	index = defined_alias(arg, aliases, len);
	if (index != -1)
	{
		free(aliases[index]), aliases[index] = _strdup(arg);
	}
	else
	{
		len = _strlen(arg), alias = malloc(len + 1);
		if (!alias)
		{
			return (1);
		}
		_strcpy(alias, arg);
		for (size = 0; aliases[size]; size++)
			;
		for (index = size; index >= 0; index--)
			aliases[index + 1] = aliases[index];
		aliases[0] = alias;
	}
	return (0);
}

/**
  * print_alias - prints an alias
  * @arg: alias
  * @aliases: array of aliases
  *
  * Return: 0 if success, 1 if it fails
  */
char print_alias(char *arg, char **aliases)
{
	size_t len;
	int index;
	char *alias;

	len = _strlen(arg) + 1, alias = malloc(len + 1);
	if (!alias)
	{
		return (1);
	}
	_strcpy(alias, arg), _strcat(alias, "=");
	index = defined_alias(alias, aliases, len);
	if (index != -1)
	{
		write(STDOUT_FILENO, aliases[index], _strlen(aliases[index]));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(alias);
	return (0);
}

/**
  * getaliasvalue - gets an alias value
  * @command: input command
  * @aliases: array of aliases
  *
  * Return: pointer to str contains alias value
  */
char *getaliasvalue(char *command, char **aliases)
{
	size_t len = _strlen(command);
	char **array = aliases;

	for (; *array != NULL; array++)
		if (!_strncmp(*array, command, len) && (*array)[len] == '=')
			return (&(*array)[len + 1]);
	return (NULL);
}

/**
  * getalias - gets value of alias if it exist
  * @command: array of command args
  * @command_argc: command arg counter
  * @aliases: array of aliases
  *
  * Return: pointer to the modified command
  */
char **getalias(char **command, size_t command_argc, char **aliases)
{
	char *value = getaliasvalue(command[0], aliases), **tokens;
	char **new_command;
	size_t tok_argc, len, i, toki = 0, comi = 1;

	if (value)
	{
		value = _strdup(value);
		if (!value)
			return (NULL);
		if (value[0] == '\'')
		{
			value[0] = ' ';
			value[_strlen(value) - 1] = ' ';
		}
		tokens = _strtok(value, " \n");
		if (!tokens)
			return (NULL);
		free(value);
		for (tok_argc = 0; tokens[tok_argc]; tok_argc++)
			;
		new_command = malloc(sizeof(char *)
				* (tok_argc + command_argc));
		if (!new_command)
			return (NULL);
		len = tok_argc + command_argc - 1;
		for (i = 0; i < len; i++)
			if (toki < tok_argc)
				new_command[i] = _strdup(tokens[toki++]);
			else
				new_command[i] = _strdup(command[comi++]);
		new_command[len] = NULL;
		free_array(tokens);
	}
	else
		new_command = command;
	return (new_command);
}
