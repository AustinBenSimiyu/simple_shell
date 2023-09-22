#include "shell.h"

/**
 * _strcmp - compare two strings
 * @one: first string to be compared
 * @two: second string to be compared
 * Return: difference of the two strings
 */

int _strcmp(char *one, char *two)
{
	int a = 0;

	while (one[a] != '\0')
	{
		if (one[a] != two[a])
			break;
		a++;
	}
	return (one[a] - two[a]);
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
	char *ns =  NULL;
	int ld = _strlen(dest);
	int ls = _strlen(src);

	ns = malloc(sizeof(*ns) * (ld + ls + 1));
	_strcpy(dest, ns);
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

	while (s1[i] != '\0')
	{
		if (_strchr(s2, s1[i]) == NULL)
			break;
		find++;
		i++;
	}
	return (find);
}

/**
 * _strcspn - computes segment of str1 which consists of characters not in str2
 * @s1: string to be searched
 * @s2: string to be used
 *
 * Return: index at which a char in s1 exists in str2
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
 * @s: string to be searched
 * @c: char to be checked
 *
 * Return: pointer to the first occurence of c in s
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
