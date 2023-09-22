#include "shell.h"

/**
 * checkcmd - determines the type of the command
 * @cmd: cmd to be parsed
 * Return: constant representing the type of the cmd
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

	for (a = 0; cmd[a] != '\0'; a++)
	{
		if (cmd[a] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (a = 0; internal_command[a] != NULL; a++)
	{
		if (_strcmp(cmd, internal_command[a]) == 0)
			return (INTERNAL_COMMAND);
	}
	path = pathc(cmd);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execcmd - executes a command based on it's type
 * @tkncmd: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @cmdtp: type of the command
 *
 * Return: void
 */
void execcmd(char **tkncmd, int cmdtp)
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
 * @cmd: cmd to be used
 *
 * Return: path where the cmd is found in, NULL if not found
 */
char *pathc(char *cmd)
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
		tmp1 = _strcat(tmp2, cmd);
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

	for (; a < 2; a++)
	{
		if (_strcmp(cmd, mapping[a].command_name) == 0)
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
