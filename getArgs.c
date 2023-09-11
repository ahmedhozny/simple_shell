#include "shell.h"

/**
 * getArgs - build arguments from input
 * @str: input string
 * @delim: delimiter
 *
 * Return: array of strings of arguments
 */
char **getArgs(const char *str, const char *delim)
{
	char *cpy, *token, **args, **tmp;
	unsigned int size = 2, i = 0;

	if (!str || !delim)
		return (NULL);
	cpy = _strdup(str);
	if (!cpy)
		return (NULL);
	token = strtok(cpy, delim);
	if (!token)
		return (free(cpy), NULL);
	args = malloc(sizeof(*args) * size);
	if (!args)
		return (free(cpy), NULL);
	while (token != NULL)
	{
		if (i + 1 >= size)
		{
			tmp = _realloc(args, sizeof(*args) * size, sizeof(*args) * size * 2);
			if (!tmp)
			{
				free(cpy);
				bigFree(args, size / 2);
				return (NULL);
			}
			size *= 2;
			args = tmp;
		}
		args[i] = _strdup(token);
		if (!args[i])
		{
			free(cpy);
			bigFree(args, size);
			return (NULL);
		}
		i++, token = strtok(NULL, delim);
	}
	args[i] = NULL;
	free(cpy);
	return (args);
}

