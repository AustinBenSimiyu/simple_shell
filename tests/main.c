#include "main.h"

/**
 * main - the shell code
 * @argc: argument count
 * @argv: arguments to be parsed
 * @ev: envir variable
 * Return: 0 success
 */
int main(int argc, char **argv, char **ev)
{
	prompt(ev);

	(void)argc, (void)argv;
	return (0);
}
/**
 * prompt - prompt printer
 * @envr: env vars
 * Return: 0
 */
int prompt(char **envr)
{
	int cn = 0;
	int exit = 0;
	char *cmmd = NULL, *new_cmmd;
	char **tk;
	list_t *ev;
	size_t i = 0, j = 0;

	ev = env_lst(envr);
	while (1)
	{
		cn++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		else
			non_interactive(ev);
		signal(SIGINT, concat);
		a = _getline(&cmmd);
		new_cmmd = cmmd;
		cmmd = space_null(cmmd);
		while (cmmd[j] != '\n')
			j++;
		cmmd[j] = '\0';
		if (cmmd[0] == '\0')
		{
			free(new_cmmd);
			continue;
		}
		tk = NULL;
		tk = _strtok(cmmd, " ");
		if (new_cmmd != NULL)
			free(new_cmmd);
		exit = exec_cmd(tk, ev, cn, NULL);
		if (exit)
		{ continue;
		}
		exit = _exe(tk, ev, cn);
	}
	return (exit);
}
