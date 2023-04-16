#include "main.h"

char *find_path(char *command)
{
	char *path_var, **all_paths, *file_path;
	int command_len, dir_len, i;
	struct stat st;

	if (stat(command, &st) == 0)
            	return (command);

	path_var = _getenv("PATH");

	if (path_var)
	{
		all_paths = _strtok(path_var, ":");
		command_len = _strlen(command);

		while (all_paths[i])
		{
			dir_len = _strlen(all_paths[i]);
			file_path = malloc(command_len + dir_len + 2);
			_strcpy(file_path, all_paths[i]);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");

			if (stat(file_path, &st) == 0)
				return (file_path);
			else
				i++;
			free(file_path);
		}

		return (NULL);
	}
	
	return (NULL);	
}
