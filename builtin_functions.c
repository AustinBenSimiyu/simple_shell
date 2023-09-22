#include "shell.h"

/**
 * env - prints the current_environnement
 * @tknc: command entered
 *
 * Return: void
 */

void env(char **tknc __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @tknc: command entered
 *
 * Return: void
 */

void quit(char **tknc)
{
	int num_token = 0, arg;

	for (; tknc[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free(tknc);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_token == 2)
	{
		arg = _atoi(tknc[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tknc[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tknc);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
