#ifndef _MAIN_H_
#define _MAIN_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
void exc(char **argv);

#endif
