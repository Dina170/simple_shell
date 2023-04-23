#include "main.h"

/**
  * helper - detect error case
  * @errnum: error case
  * @error_msg: error message
  * @msg_len: len of message
  */
void helper(char errnum, char **error_msg, size_t *msg_len)
{
	switch (errnum)
	{
		case 0:
			*error_msg = ": exit: Illegal number: ";
			break;
		case 1:
			*error_msg = ": cd: can't cd to ";
			break;
		case 2:
			*error_msg = ": setenv: too few arguments";
			break;
		case 3:
			*error_msg = ": setenv: Invalid argument: ";
			break;
		case 4:
			*error_msg = ": unsetenv: too few arguments";
			break;
		case 5:
			*error_msg = ": unsetenv: Invalid argument: ";
			break;
		case 6:
			*error_msg = ": Syntax error: \";\" unexpected";
			break;
		case 7:
			*error_msg = ": Syntax error: \";;\" unexpected";
			break;
		case 8:
			*error_msg = ": not found";
	}
	*msg_len = _strlen(*error_msg);
}

/**
 * errorHandler - prints errors to STDERR
 * @errnum: error case
 * @in_count: shell input counter
 * @farg: command first argument
 */

void errorHandler(char errnum, unsigned int in_count, char *farg)
{
	char *error_msg, *shell_err, buff[100];
	size_t msg_len = 0, len = 0;

	helper(errnum, &error_msg, &msg_len);
	len = msg_len + _strlen(_getenv("_"))
		       + _strlen(my_itoa(in_count, buff, 10))
		       + _strlen(farg) + 5;
	shell_err = malloc(len);
	_strcpy(shell_err, _getenv("_")), _strcat(shell_err, ": ");
	_strcat(shell_err, buff);
	if (errnum == 8)
	{
		_strcat(shell_err, ": ");
		_strcat(shell_err, farg);
	}
	_strcat(shell_err, error_msg);
	if (farg && errnum != 8)
		_strcat(shell_err, farg);
	_strcat(shell_err, "\n");
	write(STDERR_FILENO, shell_err, len), free(shell_err);
}
