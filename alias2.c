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
