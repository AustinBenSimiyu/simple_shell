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
	char **nowcmd = NULL;
	int i = 0, entercmd = 0;
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

		for (; commands[i] != NULL; i++)
		{
			nowcmd = tknz(commands[i], " ");
			if (nowcmd[0] == NULL)
			{
				free(nowcmd);
				break;
			}
			entercmd = checkcmd(nowcmd[0]);

			/* initializer -   */
			initializer(nowcmd, entercmd);
			free(nowcmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}
