#include "shell.h"

/**
 * init_environment - initiates lists that store environment keys and values
 * @s_i: session info
 *
 * Return: 1 on Success, 0 on failure.
 */
int init_environment(s_info *s_i)
{
	list *keys, *values;
	unsigned int i;
	char **splitted = NULL;

	keys = create_list('s');
	values = create_list('s');

	if (keys == NULL || values == NULL)
	{
		free_list(keys, 0);
		free_list(values, 0);
		return (0);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		splitted = split(environ[i], '=');
		if (!splitted)
		{
			free_list(keys, 0);
			free_list(values, 0);
			return (0);
		}
		if (!append_node(keys, splitted[0]) || !append_node(values, splitted[1]))
		{
			bigFree(splitted, 2);
			free_list(keys, 0);
			free_list(values, 0);
			return (0);
		}
		free(splitted);
	}
	s_i->env_keys = keys;
	s_i->env_vals = values;
	return (1);
}

/**
 * environment_to_array - Converts environment key-value pairs into a 2D array
 * @s_i: session info
 *
 * Return: 2d array of characters in the format of the environ schema.
 */
char **environment_to_array(s_info *s_i)
{
	node *key, *val;
	char **array;
	int i, size;

	size = list_size(s_i->env_keys);
	array = malloc((size + 1) * sizeof(*array));
	if (array == NULL)
		return (NULL);

	key = s_i->env_keys->head;
	val = s_i->env_vals->head;
	for (i = 0; i < size; i++)
	{
		array[i] = _strcat(key->d_ptr, val->d_ptr, '=');
		if (!array[i])
		{
			bigFree(array, i);
			return (NULL);
		}
		key = key->next;
		val = val->next;
	}
	return (array);
}
