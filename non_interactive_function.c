#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */

void non_interactive(void)
{
	char **cc = NULL;
	int i = 0, enterc = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			deletel(line);
			delete_cmt(line);
			commands = tkn(line, ";");
			while (commands[i] != NULL)
			{
				cc = tkn(commands[i], " ");
				if (cc[0] == NULL)
				{
					free(cc);
					break;
				}
				enterc = parse_command(cc[0]);
				initializer(cc, enterc);
				free(cc);
				i++;
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
