#include "shell.h"

/**
 * parse_command - determines the type of the command
 * @command: command to be parsed
 * Return: constant representing the type of the command
 * Description -
 * EXTERNAL_COMMAND (1) represents commands like /bin/ls
 * INTERNAL_COMMAND (2) represents commands like exit, env
 * PATH_COMMAND (3) represents commands found in the PATH like ls
 * INVALID_COMMAND (-1) represents invalid commands
 */
int parse_command(char *command)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the PATH */
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - executes a command based on it's type
 * @tkncmd: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @cmmds: type of the command
 *
 * Return: void
 */
void execute_command(char **tkncmd, int cmmds)
{
	void (*func)(char **command);

	if (cmmds == EXTERNAL_COMMAND)
	{
		if (execve(tkncmd[0], tkncmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmmds == PATH_COMMAND)
	{
		if (execve(check_path(tkncmd[0]), tkncmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmmds == INTERNAL_COMMAND)
	{
		func = get_func(tkncmd[0]);
		func(tkncmd);
	}
	if (cmmds == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tkncmd[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * get_func - retrieves a function based on the cmd given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(char **)
{
	int i = 0;

	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	while (i < 2)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
		i++;
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	char **envme;
	char *ptrtwo;
	char *cpy;

	for (envme = environ; *envme != NULL; envme++)
	{
		for (ptrtwo = *envme, cpy = name;
		     *ptrtwo == *cpy; ptrtwo++, cpy++)
		{
			if (*ptrtwo == '=')
				break;
		}
		if ((*ptrtwo == '=') && (*cpy == '\0'))
			return (ptrtwo + 1);
	}
	return (NULL);
}

/**
 * check_path - checks if a command is found in the PATH
 * @cmd: cmd to be used
 *
 * Return: path where the cmd is found in, NULL if not found
 */
char *check_path(char *cmd)
{
	char **array = NULL;
	char *tmp, *tmp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	array = tkn(path_cpy, ":");
	for (i = 0; array[i] != NULL; i++)
	{
		tmp2 = _strcat(array[i], "/");
		tmp = _strcat(tmp2, cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(tmp2);
			free(array);
			free(path_cpy);
			return (tmp);
		}
		free(tmp);
		free(tmp2);
	}
	free(path_cpy);
	free(array);
	return (NULL);
}

