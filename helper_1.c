#include "shell.h"

/**
 * _strcmp - compare two strings
 * @one: one string to be compared
 * @two: two string to be compared
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
 * @dst: string to be concatenated to
 * @src:  string to concatenate
 *
 * Return: address of the new string
 */

char *_strcat(char *dst, char *src)
{
	char *ns =  NULL;
	int ld = _strlen(dst);
	int ls = _strlen(src);

	ns = malloc(sizeof(*ns) * (ld + ls + 1));
	_strcpy(dst, ns);
	_strcpy(src, ns + ld);
	ns[ld + ls] = '\0';
	return (ns);
}

/**
 * _strspn - gets the length of a prefix substring
 * @s1: string to be searched
 * @s2: string to be used
 *
 * Return: number of bytes in the initial segment of 5 which are part of accept
 */

int _strspn(char *s1, char *s2)
{
	int i = 0;
	int find = 0;

	for (; s1[i] != '\0'; i++)
	{
		if (_strchr(s2, s1[i]) == NULL)
			break;
		find++;
	}
	return (find);
}

/**
 * _strcspn - computes segment of str1 which consists of characters not in s2
 * @s1: string to be searched
 * @s2: string to be used
 *
 * Return: index at which a char in s1 exists in s2
 */

int _strcspn(char *s1, char *s2)
{
	int len = 0, i = 0;

	for (; s1[i] != '\0'; i++)
	{
		if (_strchr(s2, s1[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 * _strchr - locates a char in a string
 * @s1: string to be searched
 * @c1: char to be checked
 *
 * Return: pointer to the first occurence of c1 in s1
 */

char *_strchr(char *s1, char c1)
{
	int i = 0;

	for (; s1[i] != c1 && s1[i] != '\0'; i++)
		;
	if (s1[i] == c1)
		return (s1 + i);
	else
		return (NULL);
}
