#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */

void non_interactive(void)
{
	char **nowcmd = NULL;
	int a = 0, entercmd = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			deletel(line);
			deletec(line);
			commands = tkn(line, ";");
			for (; commands[a] != NULL; a++)
			{
				nowcmd = tkn(commands[a], " ");
				if (nowcmd[0] == NULL)
				{
					free(nowcmd);
					break;
				}
				entercmd = checkcmd(nowcmd[0]);
				initializer(nowcmd, entercmd);
				free(nowcmd);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
