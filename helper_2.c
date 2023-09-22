#include "shell.h"

/**
 * _strtok_r - tokenizes a string
 * @str: str to be tokenized
 * @delim: delimiter to be used to tokenize the str
 * @ptrss: pointer to be used to keep track of the next token
 *
 * Return: The next available token
 */

char *_strtok_r(char *str, char *delim, char **ptrss)
{
	char *finish;

	if (str == NULL)
		str = *ptrss;

	if (*str == '\0')
	{
		*ptrss = str;
		return (NULL);
	}

	str += _strspn(str, delim);
	if (*str == '\0')
	{
		*ptrss = str;
		return (NULL);
	}

	finish = str + _strcspn(str, delim);
	if (*finish == '\0')
	{
		*ptrss = finish;
		return (str);
	}

	*finish = '\0';
	*ptrss = finish + 1;
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
 * @old_size: size of ptr
 * @new_size: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp_block;
	unsigned int i;

	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
		return (temp_block);
	}
	else if (new_size == old_size)
		return (ptr);
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		temp_block = malloc(new_size);
		if (temp_block != NULL)
		{
			for (i = 0; i < min(old_size, new_size); i++)
				*((char *)temp_block + i) = *((char *)ptr + i);
			free(ptr);
			return (temp_block);
		}
		else
			return (NULL);

	}
}

/**
 * ctrl_c_handler - handles the signal raised by CTRL-C
 * @signum: signal number
 *
 * Return: void
 */
void ctrl_c_handler(int signum)
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
