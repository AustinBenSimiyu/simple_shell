#include "shell.h"

/**
 * env - prints the current_environnement
 * @tkc: command entered
 *
 * Return: void
 */

void env(char **tkc __attribute__((unused)))
{
	int i = 0;

	for (; environ[i] != NULL; i++)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @tkc: command entered
 *
 * Return: void
 */

void quit(char **tkc)
{
	int num_token = 0, arg;

	for (; tkc[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free(tkc);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_token == 2)
	{
		arg = _atoi(tkc[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tkc[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tkc);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
