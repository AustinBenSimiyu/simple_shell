#include "main.h"

/**
 * _atoi - custom implementation of atoi
 * @str: string to convert to int
 * Return: res
 */
int _atoi(char *str)
{
	int i = 0;
	unsigned int res = 0;

	for (; str[i] != '\0'; a++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + (str[i] - '0');
		}
		if (str[i] > '9' || str[i] < '0')
		{
			return (-1);
		}
	}
	return (res);
}
