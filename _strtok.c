#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
  * isdelim - checks if char one of set of delimiter
  * @c: char to be checked
  * @delim: str of delimiters
  *
  * Return: 1 if it is delimiter, 0 otherwise
  */
char isdelim(char c, char *delim)
{
	int i;

	for (i = 0; delim[i]; i++)
		if (delim[i] == c)
			return (1);
	return (0);
}

/**
  * wordsCounter - count words in str
  * @str: str to be computed
  * @delim: tokens seperators
  *
  * Return: num of words
  */
int wordsCounter(char *str, char *delim)
{
	int words = 0, i = 0;

	while (delim[i])
	{
		if (delim[i] == *str)
		{
			break;
		}
		i++;
	}
	if (!delim[i])
		words++;
	str++;
	for (i = 1; str[i]; i++)
	{
		if (isdelim(str[i - 1], delim) && !isdelim(str[i], delim))
			words++;
	}
	return (words);
}

/**
  * free_array - free allocated array
  * @array: pointer to pointer of char
  * @size: size of array
  */
void free_array(char **array, int size)
{
	while (size--)
		free(array[size]);
	free(array);
}

/**
  * _strtok - splits str into tokens
  * @str: str to be splitted
  * @delim: tokens seperators
  *
  * Return: pointer to array of str, NULL if str = NULL or str = "" or it fails
  */
char **_strtok(char *str, char *delim)
{
	char *strcpy = str, **wordsArray;
	int words = 1, len, wordIndex = 0, i;

	if (str == (void *)'\0' || *str == '\0')
		return ((void *)'\0');
	words += wordsCounter(str, delim);
	if (words == 1)
		return ((void *)'\0');
	wordsArray = (char **)malloc(words * sizeof(char *));
	if (wordsArray != (void *)'\0')
	{
		strcpy = str;
		while (*strcpy != '\0')
		{
			len = 0;
			if (!isdelim(*strcpy, delim))
			{
				while (!isdelim(*(strcpy + len), delim) && strcpy[len] != '\0')
					len++;
				wordsArray[wordIndex] = (char *)malloc
					((len + 1) * sizeof(char));
				if (wordsArray[wordIndex] == (void *)'\0')
				{
					free_array(wordsArray, wordIndex);
					return ((void *)'\0');
				}
				for (i = 0; i < len; i++)
				{
					wordsArray[wordIndex][i] = *strcpy;
					if (i < len - 1)
						strcpy++;
				}
				wordsArray[wordIndex][len] = '\0';
				wordIndex++;
			}
			strcpy++;
		}
		wordsArray[wordIndex] = (void *)'\0';
	}
	return (wordsArray);
}
