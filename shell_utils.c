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
	int a = 0;
	char *internal_command[] = {"env", "exit", NULL};
	char *pth = NULL;

	for (a = 0; command[a] != '\0'; a++)
	{
		if (command[a] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (; internal_command[a] != NULL; a++)
	{
		if (_strcmp(command, internal_command[a]) == 0)
			return (INTERNAL_COMMAND);
	}
	pth = pathc(command);
	if (pth != NULL)
	{
		free(pth);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execcmd - executes a command based on it's type
 * @tkncmd: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @tcmd: type of the command
 *
 * Return: void
 */
void execcmd(char **tkncmd, int tcmd)
{
	void (*func)(char **command);

	if (tcmd == EXTERNAL_COMMAND)
	{
		if (execve(tkncmd[0], tkncmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (tcmd == PATH_COMMAND)
	{
		if (execve(pathc(tkncmd[0]), tkncmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (tcmd == INTERNAL_COMMAND)
	{
		func = get_func(tkncmd[0]);
		func(tkncmd);
	}
	if (tcmd == INVALID_COMMAND)
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
	char **arrp = NULL;
	char *t1, *t2, *cpyp;
	char *pth = _getenv("PATH");
	int a = 0;

	if (pth == NULL || _strlen(pth) == 0)
		return (NULL);
	cpyp = malloc(sizeof(*cpyp) * (_strlen(pth) + 1));
	_strcpy(pth, cpyp);
	arrp = tkn(cpyp, ":");
	for (; arrp[a] != NULL; a++)
	{
		t2 = _strcat(arrp[a], "/");
		t1 = _strcat(t2, command);
		if (access(t1, F_OK) == 0)
		{
			free(t2);
			free(arrp);
			free(cpyp);
			return (t1);
		}
		free(t1);
		free(t2);
	}
	free(cpyp);
	free(arrp);
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

	for (envme = environ; *envme != NULL; envme++)
	{
		for (pptr = *envme, ncpy = name;
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
