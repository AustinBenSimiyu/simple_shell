#include "shell.h"

/**
 * checkcmd - determines the type of the command
 * @cmd: command to be parsed
 *
 * Return: constant representing the type of the command
 * Description -
 * EXTERNAL_COMMAND (1) represents commands like /bin/ls
 * INTERNAL_COMMAND (2) represents commands like exit, env
 * PATH_COMMAND (3) represents commands found in the PATH like ls
 * INVALID_COMMAND (-1) represents invalid commands
 */

int checkcmd(char *cmd)
{
	int a = 0;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	while (cmd[a] != '\0')
	{
		if (cmd[a] == '/')
			return (EXTERNAL_COMMAND);
		a++;
	}
	for (; internal_command[a] != NULL; a++)
	{
		if (_strcmp(cmd, internal_command[a]) == 0)
			return (INTERNAL_COMMAND);
	}
	path = check_path(cmd);
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
		if (execve(check_path(tkncmd[0]), tkncmd, NULL) == -1)
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
 * check_path - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */

char *check_path(char *command)
{
	char **arrap = NULL;
	char *tmp1, *tmp2, *cpyp;
	char *pth = _getenv("PATH");
	int i = 0;

	if (pth == NULL || _strlen(pth) == 0)
		return (NULL);
	cpyp = malloc(sizeof(*cpyp) * (_strlen(pth) + 1));
	_strcpy(pth, cpyp);
	arrap = tknz(cpyp, ":");
	for (; arrap[i] != NULL; i++)
	{
		tmp2 = _strcat(arrap[i], "/");
		tmp1 = _strcat(tmp2, command);
		if (access(tmp1, F_OK) == 0)
		{
			free(tmp2);
			free(arrap);
			free(cpyp);
			return (tmp1);
		}
		free(tmp1);
		free(tmp2);
	}
	free(cpyp);
	free(arrap);
	return (NULL);
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @cmd: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */

void (*get_func(char *cmd))(char **)
{
	int a = 0;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	while (a < 2)
	{
		if (_strcmp(cmd, mapping[a].command_name) == 0)
			return (mapping[a].func);
		a++;
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @namess: namess of the environment variable
 *
 * Return: the value of the variable as a string
 */

char *_getenv(char *namess)
{
	char **envime;
	char *pptr;
	char *ncpy;

	for (envime = environ; *envime != NULL; envime++)
	{
		for (pptr = *envime, ncpy = namess;
		     *pptr == *ncpy; pptr++, ncpy++)
		{
			if (*pptr == '=')
				break;
		}
		if ((*pptr == '=') && (*ncpy == '\0'))
			return (pptr + 1);
	}
	return (NULL);
}
