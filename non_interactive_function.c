#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */

void non_interactive(void)
{
	char **cccmd = NULL;
	int i = 0, tcmd = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			deletel(line);
			deletec(line);
			commands = tkn(line, ";");
			for (i = 0; commands[i] != NULL; i++)
			{
				cccmd = tkn(commands[i], " ");
				if (cccmd[0] == NULL)
				{
					free(cccmd);
					break;
				}
				tcmd = checkcmd(cccmd[0]);
				initializer(cccmd, tcmd);
				free(cccmd);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
