#include "shell.h"

/**
 * initializer - starts executing everything
 * @cc: try to check current token
 * @enter_c: parse token
 *
 * Return: void function
 */

void initializer(char **cc, int enter_c)
{
	pid_t PID;

	if (enter_c == EXTERNAL_COMMAND || enter_c == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_command(cc, enter_c);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(cc, enter_c);
}
