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

extern char **environ;
extern char *program_name;
extern unsigned long in_count;

/**
  * struct builtin_command - Struct
  *
  * @command: command
  * @f: The function associated
  */
typedef struct builtin_command
{
	char *command;
	void (*f)(char **);
} com_t;

ssize_t getline(char **, size_t *, FILE *);
void exec(char **, char **);
char *_strcpy(char *, char *);
char **_strtok(char *, char *);
char *_getenv(char *);
int _strlen(char *);
int _strncmp(char *, char *, size_t);
char *find_path(char *);
char *_strcat(char *, char *);
char *_strrev(char *);
int _atoi(char *, char *);
char *my_itoa(long int, char *, int);
void shell_exit(char **);
void shell_env(char **);
void shell_cd(char **);

#endif /* ifndef _MAIN_H_ */
