#include "shell.h"

/**
 * checkcmd - determines the type of the command
 * @command: command to be parsed
 * Return: constant representing the type of the command
 * Description -
 * EXTERNAL_COMMAND (1) represents commands like /bin/ls
 * INTERNAL_COMMAND (2) represents commands like exit, env
 * PATH_COMMAND (3) represents commands found in the PATH like ls
 * INVALID_COMMAND (-1) represents invalid commands
 */
int checkcmd(char *command)
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
	path = pathc(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execcmd - executes a command based on it's type
 * @tokenized_command: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @command_type: type of the command
 *
 * Return: void
 */
void execcmd(char **tokenized_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execve(pathc(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_func(tokenized_command[0]);
		func(tokenized_command);
	}
	if (command_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *pathc(char *command)
{
	char **arrap = NULL;
	char *tmp1, *tmp2, *pcpy;
	char *ph = _getenv("PATH");
	int a;

	if (ph == NULL || _strlen(ph) == 0)
		return (NULL);
	pcpy = malloc(sizeof(*pcpy) * (_strlen(ph) + 1));
	_strcpy(ph, pcpy);
	arrap = tkn(pcpy, ":");
	for (a = 0; arrap[a] != NULL; a++)
	{
		tmp2 = _strcat(arrap[a], "/");
		tmp1 = _strcat(tmp2, command);
		if (access(tmp1, F_OK) == 0)
		{
			free(tmp2);
			free(arrap);
			free(pcpy);
			return (tmp1);
		}
		free(tmp1);
		free(tmp2);
	}
	free(pcpy);
	free(arrap);
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
	char *ncpy;

	envme = environ; 
	while (*envme != NULL)
	{
		for (pptr = *envme, ncpy = name;
		     *pptr == *ncpy; pptr++, ncpy++)
		{
			if (*pptr == '=')
				break;
		}
		if ((*pptr == '=') && (*ncpy == '\0'))
			return (pptr + 1);
		envme++;
	}
	return (NULL);
}
