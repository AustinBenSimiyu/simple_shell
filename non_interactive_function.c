#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */

void non_interactive(void)
{
	char **current_command = NULL;
	int a = 0, type_command = 0;
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
				current_command = tkn(commands[a], " ");
				if (current_command[0] == NULL)
				{
					free(current_command);
					break;
				}
				type_command = checkcmd(current_command[0]);
				initializer(current_command, type_command);
				free(current_command);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
