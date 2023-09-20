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
	char **curr_cmmd = NULL;
	int i = 0, type_command = 0;
	size_t n = 0;

	signal(SIGINT, ctrl_c_handler);
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
			remove_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");

		for (; commands[i] != NULL; i++)
		{
			curr_cmmd = tokenizer(commands[i], " ");
			if (curr_cmmd[0] == NULL)
			{
				free(curr_cmmd);
				break;
			}
			type_command = parse_command(curr_cmmd[0]);

			/* initializer -   */
			initializer(curr_cmmd, type_command);
			free(curr_cmmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}
