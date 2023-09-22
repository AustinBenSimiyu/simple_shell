#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */

void non_interactive(void)
{
	char **ccmd = NULL;
	int a = 0, enterccmd = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			deletel(line);
			deletec(line);
			commands = tknz(line, ";");
			for (; commands[a] != NULL; a++)
			{
				ccmd = tknz(commands[a], " ");
				if (ccmd[0] == NULL)
				{
					free(ccmd);
					break;
				}
				enterccmd = checkcmd(ccmd[0]);
				initializer(ccmd, enterccmd);
				free(ccmd);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
