#include "shell.h"

/**
 * checkcmd - determines the type of the command
 * @command: command to be parsed
 * Return: constant representing the type of the command
 */
int checkcmd(char *command)
{
	int a = 0;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (; command[a] != '\0'; a++)
	{
		if (command[a] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (; internal_command[a] != NULL; a++)
	{
		if (_strcmp(command, internal_command[a]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the PATH */
	path = pathc(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execmd - executes a command based on it's type
 * @tkncmd: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @cmdtp: type of the command
 *
 * Return: void
 */
void execmd(char **tkncmd, int cmdtp)
{
	void (*func)(char **command);

	if (cmdtp == EXTERNAL_COMMAND)
	{
		if (execve(tkncmd[0], tkncmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmdtp == PATH_COMMAND)
	{
		if (execve(pathc(tkncmd[0]), tkncmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmdtp == INTERNAL_COMMAND)
	{
		func = get_func(tkncmd[0]);
		func(tkncmd);
	}
	if (cmdtp == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tkncmd[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * pathc - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *pathc(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tkn(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(char **)
{
	int a = 0;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (; a < 2; a++)
	{
		if (_strcmp(command, mapping[a].command_name) == 0)
			return (mapping[a].func);
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
	char *pptr;
	char *ncpr;

	for (envme = environ; *envme != NULL; envme++)
	{
		for (pptr = *envme, ncpr = name;
		     *pptr == *ncpr; pptr++, ncpr++)
		{
			if (*pptr == '=')
				break;
		}
		if ((*pptr == '=') && (*ncpr == '\0'))
			return (pptr + 1);
	}
	return (NULL);
}
