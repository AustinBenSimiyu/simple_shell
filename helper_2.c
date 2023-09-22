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
	char *endss;

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

	endss = str + _strcspn(str, delim);
	if (*endss == '\0')
	{
		*sptr = endss;
		return (str);
	}

	*endss = '\0';
	*sptr = endss + 1;
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
	unsigned int a = 0;

	do {
		if (*str == '-')
			return (-1);
		else if ((*str < '0' || *str > '9') && *str != '\0')
			return (-1);
		else if (*str >= '0'  && *str <= '9')
			a = (a * 10) + (*str - '0');
		else if (a > 0)
			break;
	} while (*str++);
	return (a);
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
	void *tblk;
	unsigned int a = 0;

	if (ptr == NULL)
	{
		tblk = malloc(ns);
		return (tblk);
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
		tblk = malloc(ns);
		if (tblk != NULL)
		{
			for (; a < min(os, ns); a++)
				*((char *)tblk + a) = *((char *)ptr + a);
			free(ptr);
			return (tblk);
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
	int a = 0;

	if (input[a] == '#')
		input[a] = '\0';
	while (input[a] != '\0')
	{
		if (input[a] == '#' && input[a - 1] == ' ')
			break;
		a++;
	}
	input[a] = '\0';
}
