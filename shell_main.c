#include "shell.h"

	char **commands = NULL;
	char *line = NULL;
	char *shell_name = NULL;
	int status = 0;

/**
 * main - the main shell code
 * @ac: number of arguments passed
 * @av: program arguments to be parsed
 * Prints error on Failure
 * Return: 0 on success
 */

int main(int ac __attribute__((unused)), char **av)
{
	char **cmd = NULL;
	int i = 0, inputcmd = 0;
	size_t n = 0;

	signal(SIGINT, controlc);
	shell_name = av[0];
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
			delete_cmt(line);
			commands = tkn(line, ";");

		for (; commands[i] != NULL; i++)
		{
			cmd = tkn(commands[i], " ");
			if (cmd[0] == NULL)
			{
				free(cmd);
				break;
			}
			inputcmd = parse_command(cmd[0]);

			/* initializer -   */
			initializer(cmd, inputcmd);
			free(cmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}
