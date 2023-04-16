#include "main.h"

/**
  * _strcpy - copies str pointed to by src to dest
  * @dest: pointer to buffer
  * @src: pointer to str to be copied
  *
  * Return: pointer to dest
  */
char *_strcpy(char *dest, char *src)
{
	char *destcpy = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (destcpy);
}

/**
  * _strlen - computes len of a string
  * @s: string to be checked
  *
  * Return: len of s
  */
int _strlen(char *s)
{
	int i;

	for (i = 0; *s != '\0'; i++)
	{
		s++;
	}
	return (i);
}

/**
  * _strncmp - compares two strs to n bytes
  * @s1: first str to be compared
  * @s2: second str to be compared
  * @n: num of bytes to be compared
  *
  * Return: corresponding to n, 0 if the s1 & s2 are equal
  * a negative value if s1 is less than s2
  * a positive value if s1 is greater than s2
  */
int _strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 != '\0' && *s2 != '\0' && --n)
	{
		if (*s1 != *s2)
		{
			break;
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
  * _strcat - Concatenates two strings
  * @dest: The destination string
  * @src: The source string
  *
  * Return: A pointer to the resulting string dest
  */
char *_strcat(char *dest, char *src)
{
	int dlen = 0, i;

	while (dest[dlen])
	{
		dlen++;
	}

	for (i = 0; src[i] != 0; i++)
	{
		dest[dlen] = src[i];
		dlen++;
	}

	dest[dlen] = '\0';
	return (dest);
}

/**
 * _strrev - Reverses a string.
 * @str: The string to be reversed.
 *
 * Return: pointer to reversed string
 */
char *_strrev(char *str)
{
	int i,	j = 0;
	char temp;

	while (str[j])
	{
		j++;
	}

	for (i = 0; i < j / 2; i++)
	{
		temp = str[i];
		str[i] = str[j - i - 1];
		str[j - i - 1] = temp;
	}
	return (str);
}
