#include "shell.h"

/**
 * _strtok - tokenizes a string
 * @str: string to be tokenized
 * @delim: delimiter to be used to tokenize the string
 * @ptr_s: pointer to be used to keep track of the next token
 *
 * Return: The next available token
 */
char *_strtok(char *str, char *delim, char **ptr_s)
{
	char *ends;

	if (str == NULL)
		str = *ptr_s;

	if (*str == '\0')
	{
		*ptr_s = str;
		return (NULL);
	}

	str += _strspn(str, delim);
	if (*str == '\0')
	{
		*ptr_s = str;
		return (NULL);
	}

	ends = str + _strcspn(str, delim);
	if (*ends == '\0')
	{
		*ptr_s = ends;
		return (str);
	}

	*ends = '\0';
	*ptr_s = ends + 1;
	return (str);
}

/**
 * _atoi - changes a string to an integer
 * @str: the string to be changed
 *
 * Return: the converted int
 */
int _atoi(char *str)
{
	unsigned int n = 0;

	do {
		if (*str == '-')
			return (-1);
		else if ((*str < '0' || *str > '9') && *str != '\0')
			return (-1);
		else if (*str >= '0'  && *str <= '9')
			n = (n * 10) + (*str - '0');
		else if (n > 0)
			break;
	} while (*str++);
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
	void *blockers;
	unsigned int i = 0;

	if (ptr == NULL)
	{
		blockers = malloc(ns);
		return (blockers);
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
		blockers = malloc(ns);
		if (blockers != NULL)
		{
			for (; i < min(os, ns); i++)
			{
				*((char *)blockers + i) = *((char *)ptr + i);
			}
			free(ptr);
			return (blockers);
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
 * remove_comment - removes/ignores everything after a '#' char
 * @input: input to be used
 *
 * Return: void
 */
void remove_comment(char *input)
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
