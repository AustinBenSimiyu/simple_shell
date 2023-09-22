#include "shell.h"

/**
 * tkn - tokenizes input and stores it into an array
 * @str: input to be parsed
 * @delim: delimiter to be used, needs to be one character string
 *
 * Return: array of tokens
 */

char **tkn(char *str, char *delim)
{
	int num = 0;
	char **bc = NULL;
	char *tkn = NULL;
	char *ptr = NULL;

	tkn = _strtok(str, delim, &ptr);

	while (tkn != NULL)
	{
		bc = _realloc(bc, sizeof(*bc) * num, sizeof(*bc) * (num + 1));
		bc[num] = tkn;
		tkn = _strtok(NULL, delim, &ptr);
		num++;
	}

	bc = _realloc(bc, sizeof(*bc) * num, sizeof(*bc) * (num + 1));
	bc[num] = NULL;

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
	int a = 0;

	for (; str[a] != '\0'; a++)
	{
		write(strm, &str[a], 1);
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
	int a = 0;

	while (str[a] != '\0')
	{
		if (str[a] == '\n')
			break;
		a++;
	}

	str[a] = '\0';
}

/**
 * _strcpy - copies a string to another buffer
 * @src: source to copy from
 * @dest: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *src, char *dest)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
}

/**
 * _strlen - counts string length
 * @str: string to be counted
 *
 * Return: length of the string
 */

int _strlen(char *str)
{
	int l = 0;

	if (str == NULL)
	{
		return (l);
	}

	for (; str[l] != '\0'; l++)
		;
	return (l);
}
