#include "shell.h"

/**
 * search_PATH - searches PATH for needed command
 * @s_i: pointer to current session info
 * @cmd: command to be searched for
 *
 * Return: full command if exits
 * or NULL if not
 */
char *search_PATH(s_info *s_i, char *cmd)
{
	char **path, *full_cmd;
	node *pathenv = _getenv(s_i, "PATH");
	int i = 0;

	if (!pathenv)
		return (free(cmd), NULL);
	path = strtow(pathenv->d_ptr, ':');
	if (!path)
	{
		s_i->status = 97;
		return (free(cmd), NULL);
	}
	while (path[i])
	{
		full_cmd = _strcat(path[i], cmd, path[i][0]);
		if (!full_cmd)
		{
			bigFree(path, -1);
			s_i->status = 97;
			return (free(cmd), NULL);
		}
		if (!access(full_cmd, X_OK))
		{
			bigFree(path, -1);
			return (free(cmd), full_cmd);
		}
		free(full_cmd);
		i++;
	}
	bigFree(path, -1);
	return (free(cmd), NULL);
}

/**
 * exec_builtin - execute proper built-in function
 * @s_i: session info
 * @args: arguments to the built-in command
 * @cmd: string to the called function
 *
 * Return: 1 on Success, 0 Otherwise
 */
int exec_builtin(s_info *s_i, char **args, char *cmd)
{
	if (!_strcmp(cmd, "env"))
		print_env(s_i);
	else if (!_strcmp(cmd, "setenv"))
		_setenv(s_i, args[0], args[1]);
	else if (!_strcmp(cmd, "unsetenv"))
		_unsetenv(s_i, args[0]);
	else if (!_strcmp(cmd, "exit"))
		exit_sh(s_i, args);
	else
		return (0);
	return (1);
}
