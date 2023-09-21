#include "main.h"

/**
 * _size - ...
 * @str: ...
 * @delm: ...
 * Return: 0
 */
int _size(char *str, char delm)
{
	int i = 0;
	int count = 0;

	for (; str[i] != '\0'; i++)
	{
		if (str[i] == delm)
		{
			count++;
		}
		i++;
	}
	return (count);
}

/**
 * _token - tokenize a string
 * @str: cmd
 * @delm: delimeter
 * Return: array
 */
int **_token(char *str, char *delm)
{
	char **tknise = NULL, chrs = delm[0];
	int buffs = 0, i = 0, j = 0, k = 0, l = 0, m = 0;

	buffs = _size(str, chrs);

	tknise = malloc(sizeof(char *) * (buffs + 2));
	if (tknise == NULL)
	{
		return  (NULL);
	}
	for (m = 0; str[m] != '\0'; m++)
		;
	for (j = 0; j < m; i++)
	{
		l = _strlen(str, j, chrs);
		tknise[i] = malloc(sizeof(chrs) * (l + 1));
		if (tknise[i] == NULL)
		{
			return (NULL);
		}
		for (k = 0; (str[j] != chrs) && (str[j] != '\0'); k++, j++)
		{
			tknise[i][k] = str[j];
		}
		tknise[i][k] = '\0';
		j++;
	}
	tknise[i] = NULL;
	return (tknise);
}
