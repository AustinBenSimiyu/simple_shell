#include "shell.h"

/**
 * tknz - tokenizes input and stores it into an array
 * @str: input to be parsed
 * @delim: delimiter to be used, needs to be one character string
 *
 * Return: array of tokens
 */

char **tknz(char *str, char *delim)
{
	int numz = 0;
	char **bc = NULL;
	char *tkn = NULL;
	char *ptrs = NULL;

	tkn = _strtok(str, delim, &ptrs);
	while (tkn != NULL)
	{
		bc = _realloc(bc, sizeof(*bc) * numz, sizeof(*bc) * (numz + 1));
		bc[numz] = tkn;
		tkn = _strtok(NULL, delim, &ptrs);
		numz++;
	}

	bc = _realloc(bc, sizeof(*bc) * numz, sizeof(*bc) * (numz + 1));
	bc[numz] = NULL;

	return (bc);
}

/**
 * print - prints a string to stdout
 * @str: string to be printed
 * @strm: stream to print out to
 *
 * Return: void, return nothing
 */
void print(char *str, int strm)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
	{
		write(strm, &str[i], 1);
	}
}

/**
 * deletel - removes new line from a string
 * @str: string to be used
 *
 * Return: void
 */

void deletel(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	str[i] = '\0';
}

/**
 * _strcpy - copies a string to another buffer
 * @src: src to copy from
 * @dst: dstination to copy to
 *
 * Return: void
 */

void _strcpy(char *src, char *dst)
{
	int i = 0;

	for (; src[i] != '\0'; i++)
		dst[i] = src[i];
	dst[i] = '\0';
}

/**
 * _strlen - counts string length
 * @str: string to be counted
 *
 * Return: length of the string
 */

int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (len);
	for (; str[len] != '\0'; len++)
		;
	return (len);
}
