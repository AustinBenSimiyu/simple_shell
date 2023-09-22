#include "shell.h"

/**
 * initializer - starts executing everything
 * @ccone: try to check current token
 * @enterc: parse token
 *
 * Return: void function
 */

void initializer(char **ccone, int enterc)
{
	pid_t PID;

	if (enterc == EXTERNAL_COMMAND || enterc == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_command(ccone, enterc);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
	{
		execute_command(ccone, enterc);
	}
}
