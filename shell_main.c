#include "shell.h"

	char **commands = NULL;
	char *line = NULL;
	char *shell_name = NULL;
	int status = 0;

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char **ccmd = NULL;
	int i = 0, enterccmd = 0;
	size_t n = 0;

	signal(SIGINT, controlc);
	shell_name = argv[0];
	while (1)
	{
		non_interactive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
			deletel(line);
			deletec(line);
			commands = tknz(line, ";");

		for (i = 0; commands[i] != NULL; i++)
		{
			ccmd = tknz(commands[i], " ");
			if (ccmd[0] == NULL)
			{
				free(ccmd);
				break;
			}
			enterccmd = parse_command(ccmd[0]);

			initializer(ccmd, enterccmd);
			free(ccmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}
