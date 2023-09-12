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

	path = getArgs(getenv("PATH"), ":");
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
