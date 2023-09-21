#include "main.h"

/**
 * _set_env - custom implementation of setenv
 * @ev: env list
 * @num: variable name
 * @d: directory variable
 * Return: 0
 /
int _set_env(list_t **ev, char *num, char *d);
{
	char *ch;
	list_t *hl;
	int i = 0, a = 0;

	ch = _strdup(num);
	ch = _strcat(ch, "=");
	ch = _strcat(ch, d);
	i = get_envr(*ev, num);

	hl = *ev;
	for (; a < i; a++)
	{
		hl = hl->next;
	}
	free(hl->var);
	hl->var = _strdup(ch);
	free(ch);
	return (0);
}

/**
 * _home - changes to home
 * @ev: update to PATH
 * @curr: current path
 /
void _home(list_t *ev, char *curr)
{
	char *base = NULL;

	base = env_find("HOME", ev);
	_set_env(&ev, "OLDPWD", curr);
	free(curr);

	if (access(base, F_OK) == 0)
		chdir(base);

	curr = NULL;
	curr = getcwd(curr, 0);
	_set_env(&ev, "PWD", curr);
	free(curr);
	free(base);
}

/**
 * exe_cd - executes cd
 * @ev: var
 * @curr: current
 * @dir: directory
 * @str: string arg
 * @num: number of args
 * Return: 0
 /
int exec_cd(list_t *ev, char *curr, char *dir, char *str, int num);
{
	int i;

	if (access(dir, F_OK) == 0)
	{
		_set_env(&ev, "OLDPWD", curr);
		free(curr);
		chdir(dir);
		curr = NULL;
		curr = getcwd(curr, 0);
		_set_env(&ev, "PWD", curr);
		free(curr);
	}
	else
	{
		no_dir_changes(str, num, ev);
		free(curr);
		i = 2;
	}
	return (i);
}
/**
 * _cd - change dir
 * @str: cmd
 * @ev: environment
 * @num: n command
 * Return: 0
/
int _cd(char **str, list_t *ev, int num);
{
	int ext = 0;
	char *curr = NULL, *a = NULL;

	curr = getcwd(curr);
	if (str[1] != NULL)
	{
		if (str[1][0] == '~')
		{
			a = env_find("HOME", ev);
			a = _strcat(a, str[1]);
		}
		else if (str[1][0] == '-')
		{
			if (str[1][1] == '\0')
			{
				a = env_find("OLDPWD", ev);
			}
		}
		else
		{
			if (str[1][0] != '/')
			{
				a = getcwd(a, 0);
				a = _strcat(a, "/");
				a = _strcat(a, str[1]);
			}
			else
			{
				a = _strdup(str[1]);
			}
		}
		ext = exe_cd(ev, curr, dir, str[1], num);
		free(a);
	}
	else
	{
		_home(ev, curr);
	}
	_free(str);
	return (ext);
}
*/
