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

	if (!pathenv)
		return (NULL);
	path = strtow(pathenv->d_ptr, ':');
	if (!path)
	{
		s_i->status = 97;
		return (NULL);
	}
	while (path && *path)
	{
		full_cmd = _strcat(*path, cmd, (*path)[0]);
		if (!full_cmd)
		{
			s_i->status = 97;
			return (NULL);
		}
		if (!access(full_cmd, X_OK))
			return (full_cmd);
		free(full_cmd);
		path++;
	}
	return (NULL);
}

/**
 * get_builtin - get function that corresponds
 * to the called built-in
 * @str: string to the called function
 *
 * Return: pointer to proper function
 */
int (*get_builtin(char *str))(s_info *s_i, char **args)
{
	builtin b_i[] = {
		{"env", print_env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"exit", exit_sh},
		{"cd", change_dir},
		{"alias", alias_handler}
		{NULL, NULL}
	};
	int i = 0;

	while (b_i[i].str)
	{
		if (!_strcmp(b_i[i].str, str))
			return (b_i[i].func);
		i++;
	}
	return (NULL);
}
