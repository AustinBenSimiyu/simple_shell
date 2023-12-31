#include "shell.h"

	char **commands = NULL;
	char *line = NULL;
	char *shell_name = NULL;
	int status = 0;

/**
 * main - the main shell code
 * @ac: number of arguments passed
 * @av: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */

int main(int ac __attribute__((unused)), char **av)
{
	char **current_command = NULL;
	int a, type_command = 0;
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
			deletec(line);
			commands = tkn(line, ";");

		for (a = 0; commands[a] != NULL; a++)
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

	return (status);
}
