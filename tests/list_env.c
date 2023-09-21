#include "main.h"

/**
 * env_lst - create linked list
 * @ev: environment var
 * Return: list
 */
list_t *env_lst(char **ev)
{
	list_t *above;
	int i = 0;

	for (above = NULL; ev[i] != NULL; i++)
	{
		append_node(&above, ev[i]);
	}
	return (above);
}
/**
 * builtin_env - prints env
 * @str: string cmd
 * @ev: environment
 * Return: 0
 */
int builtin_env(char **str, list_t *ev)
{
	_free(str);
	_printf(ev);

	return (0);
}
