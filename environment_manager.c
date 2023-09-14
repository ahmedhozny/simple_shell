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
	char **split;

	keys = create_list('s');
	values = create_list('s');

	if (keys == NULL || values == NULL)
		return (0);

	for (i = 0; environ[i] != NULL; i++)
	{
		split = strtow(environ[i], '=');
		if (!split)
			return (0);
		if (!append_node(keys, split[0]) || !append_node(values, split[1]))
			return (0);
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

/**
 * _getenv - gets value associated with a given key in the environment
 * @s_i: session info
 * @key: key to search for in the environment
 *
 * Return: pointer to the desired node if found, NULL if not found.
 */
node *_getenv(s_info *s_i, char *key)
{
	node *keys = s_i->env_keys->head;
	node *vals = s_i->env_vals->head;

	while (keys && vals)
	{
		if (!_strcmp(keys->d_ptr, key))
			return (vals);
		vals = vals->next;
		keys = keys->next;
	}

	return (NULL);
}

/**
 * _setenv - sets or updates a key-value pair in the environment
 * @s_i: session info
 * @key: the key for the environment variable
 * @val: the value to associate with the key
 *
 * Return: 0 on Success, 1 on failure
 */
int _setenv(s_info *s_i, char *key, char *val)
{
	node *c = _getenv(s_i, key);

	if (c == NULL)
	{
		if (!append_node(s_i->env_keys, key) || !append_node(s_i->env_vals, val))
			return (1);
	}
	else
	{
		if (!amend_node(s_i->env_vals, c - s_i->env_keys->head, val))
			return (1);
	}

	return (0);
}
