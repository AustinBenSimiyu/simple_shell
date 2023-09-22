#include "shell.h"

/**
 * _strtok - tokenizes a string
 * @str: str to be tokenized
 * @delim: delimiter to be used to tokenize the str
 * @sptr: pointer to be used to keep track of the next token
 *
 * Return: The next available token
 */

char *_strtok(char *str, char *delim, char **sptr)
{
	char *ends;

	if (str == NULL)
		str = *sptr;

	if (*str == '\0')
	{
		*sptr = str;
		return (NULL);
	}

	str += _strspn(str, delim);
	if (*str == '\0')
	{
		*sptr = str;
		return (NULL);
	}

	ends = str + _strcspn(str, delim);
	if (*ends == '\0')
	{
		*sptr = ends;
		return (str);
	}

	*ends = '\0';
	*sptr = ends + 1;
	return (str);
}

/**
 * _atoi - changes a string to an integer
 * @s: the string to be changed
 *
 * Return: the converted int
 */

int _atoi(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @os: size of ptr
 * @ns: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */

void *_realloc(void *ptr, unsigned int os, unsigned int ns)
{
	void *blockt;
	unsigned int i = 0;

	if (ptr == NULL)
	{
		blockt = malloc(ns);
		return (blockt);
	}
	else if (ns == os)
		return (ptr);
	else if (ns == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		blockt = malloc(ns);
		if (blockt != NULL)
		{
			for (i = 0; i < min(os, ns); i++)
				*((char *)blockt + i) = *((char *)ptr + i);
			free(ptr);
			return (blockt);
		}
		else
			return (NULL);

	}
}

/**
 * controlc - handles the signal raised by CTRL-C
 * @signum: signal number
 *
 * Return: void
 */
void controlc(int signum)
{
	if (signum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * deletec - removes/ignores everything after a '#' char
 * @input: input to be used
 *
 * Return: void
 */

void deletec(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}
