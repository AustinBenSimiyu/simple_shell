#include "shell.h"

/**
 * tokenizer - tokenizes input and stores it into an array
 * @enters: input to be parsed
 * @delim: delimiter to be used, needs to be one character string
 *
 * Return: array of tokens
 */

char **tokenizer(char *enters, char *delim)
{
	int nums = 0;
	char **avc = NULL;
	char *tkn = NULL;
	char *sptr = NULL;

	tkn = _strtok_r(enters, delim, &sptr);

	while (tkn != NULL)
	{
		avc = _realloc(avc, sizeof(*avc) * nums, sizeof(*avc) * (nums + 1));
		avc[nums] = tkn;
		tkn = _strtok_r(NULL, delim, &sptr);
		nums++;
	}

	avc = _realloc(avc, sizeof(*avc) * nums, sizeof(*avc) * (nums + 1));
	avc[nums] = NULL;

	return (avc);
}

/**
 * print - prints a string to stdout
 * @str: str to be printed
 * @strm: strm to print out to
 *
 * Return: void, return nothing
 */
void print(char *str, int strm)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
		write(strm, &str[i], 1);
}

/**
 * remove_newline - removes new line from a string
 * @str: string to be used
 *
 * Return: void
 */

void remove_newline(char *str)
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
 * @source: source to copy from
 * @dest: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *source, char *dest)
{
	int i = 0;

	for (; source[i] != '\0'; i++)
		dest[i] = source[i];
	dest[i] = '\0';
}

/**
 * _strlen - counts string length
 * @string: string to be counted
 *
 * Return: length of the string
 */

int _strlen(char *string)
{
	int len = 0;

	if (string == NULL)
		return (len);
	for (; string[len] != '\0'; len++)
		;
	return (len);
}
