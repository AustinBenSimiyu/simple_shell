#include "shell.h"

/**
 * env - prints the current_environnement
 * @tkncmd: command entered
 *
 * Return: void
 */

void env(char **tkncmd __attribute__((unused)))
{
	int a = 0;

	for (; environ[a] != NULL; a++)
	{
		print(environ[a], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @tkncmd: command entered
 *
 * Return: void
 */

void quit(char **tkncmd)
{
	int numtk = 0, arg;

	for (; tkncmd[numtk] != NULL; numtk++)
		;
	if (numtk == 1)
	{
		free(tkncmd);
		free(line);
		free(commands);
		exit(status);
	}
	else if (numtk == 2)
	{
		arg = _atoi(tkncmd[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tkncmd[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tkncmd);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
