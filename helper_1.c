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
	int a = 0;

	for (; one[a] != '\0'; a++)
	{
		if (one[a] != two[a])
			break;
	}
	return (one[a] - two[a]);
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
	int a = 0;
	int find = 0;

	for (; s1[a] != '\0'; a++)
	{
		if (_strchr(s2, s1[a]) == NULL)
			break;
		find++;
	}
	return (find);
}

/**
 * _strcspn - computes segment of s1 which consists of characters not in s2
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: index at which a char in str1 exists in str2
 */

int _strcspn(char *str1, char *str2)
{
	int len = 0, a = 0;

	for (; str1[a] != '\0'; a++)
	{
		if (_strchr(str2, str1[a]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 * _strchr - locates a char in a string
 * @str: string to be searched
 * @ch: char to be checked
 *
 * Return: pointer to the first occurence of ch in str
 */

char *_strchr(char *str, char ch)
{
	int a = 0;

	while (str[a] != ch && str[a] != '\0')
	{
		a++;
	}
	if (str[a] == ch)
		return (str + a);
	else
		return (NULL);
}
