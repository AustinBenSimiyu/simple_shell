#include "shell.h"

/**
 * _strcmp - compare two strings
 * @one: one string to be compared
 * @two: second string to be compared
 *
 * Return: difference of the two strings
 */

int _strcmp(char *one, char *two)
{
	int i = 0;

	for (; one[i] != '\0'; i++)
	{
		if (one[i] != two[i])
			break;
	}
	return (one[i] - two[i]);
}

/**
 * _strcat - concatenates two strings
 * @dest: string to be concatenated to
 * @src:  string to concatenate
 *
 * Return: address of the new string
 */

char *_strcat(char *dest, char *src)
{
	char *sn =  NULL;
	int ld = _strlen(dest);
	int ls = _strlen(src);

	sn = malloc(sizeof(*sn) * (ld + ls + 1));

	_strcpy(dest, sn);
	_strcpy(src, sn + ld);
	sn[ld + ls] = '\0';

	return (sn);
}

/**
 * _strspn - gets the length of a prefix substring
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: number of bytes in the initial segment of 5 which are part of accept
 */

int _strspn(char *str1, char *str2)
{
	int i = 0;
	int match = 0;

	while (str1[i] != '\0')
	{
		if (_strchr(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}

	return (match);
}

/**
 * _strcspn - computes segment of str1 which consists of characters not in str2
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: index at which a char in str1 exists in str2
 */

int _strcspn(char *str1, char *str2)
{
	int len = 0, i = 0;

	for (; str1[i] != '\0'; i++)
	{
		if (_strchr(str2, str1[i]) != NULL)
			break;
		len++;
	}

	return (len);
}

/**
 * _strchr - locates a char in a string
 * @str: string to be searched
 * @cc: char to be checked
 *
 * Return: pointer to the first occurence of c in s
 */

char *_strchr(char *str, char cc)
{
	int i = 0;

	for (; str[i] != cc && str[i] != '\0'; i++)
		;
	if (str[i] == cc)
	{
		return (str + i);
	}
	else
	{
		return (NULL);
	}
}
