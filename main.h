#ifndef _MAIN_H_
#define _MAIN_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <linux/limits.h>
#include <fcntl.h>

extern char **environ;

/**
  * struct builtin_command - Struct
  *
  * @command: command
  * @f: The function associated
  */
typedef struct builtin_command
{
	char *command;
	size_t (*f)(char **, unsigned long);
} com_t;

ssize_t getline(char **, size_t *, FILE *);
size_t exec(char **, unsigned long, char **);
char *_strcpy(char *, char *);
char *_strncpy(char *, char *, int);
char **_strtok(char *, char *);
char *_getenv(char *);
int _strlen(char *);
int _strncmp(char *, char *, size_t);
char *find_path(char *);
char *_strcat(char *, char *);
char *_strrev(char *);
int _atoi(char *, char *);
char *my_itoa(long int, char *, int);
size_t shell_exit(char **, unsigned long);
size_t shell_env(char **, unsigned long);
size_t shell_cd(char **, unsigned long);
size_t _setenv(char **, unsigned long);
size_t _unsetenv(char **, unsigned long);
void errorHandler(char, unsigned int, char *);
ssize_t _getline(char **, size_t *, FILE *);
ssize_t concat_sep(char **);

#endif /* ifndef _MAIN_H_ */
