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
		append_node(keys, split[0]);
		append_node(values, split[1]);
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

	array = malloc(list_size(s_i->env_keys) * sizeof(char *));
	if (array == NULL)
		return (NULL);

	size = list_size(s_i->env_keys);
	key = s_i->env_keys->head;
	val = s_i->env_vals->head;
	for (i = 0; i < size; i++)
	{
		array[i] = _strcat(key->d_ptr, val->d_ptr, '=');
		key = key->next;
		val = val->next;
	}
	return (array);
}

/**
 * get_environment - gets value associated with a given key in the environment
 * @s_i: session info
 * @key: key to search for in the environment
 *
 * Return: pointer to the desired node if found, NULL if not found.
 */
node *get_environment(s_info *s_i, char *key)
{
	node *c = s_i->env_keys->head;

	while (c != NULL)
	{
		if (!_strcmp(c->d_ptr, key))
			break;
		c = c->next;
	}

	return (c);
}

/**
 * set_environment - sets or updates a key-value pair in the environment
 * @s_i: session info
 * @key: the key for the environment variable
 * @val: the value to associate with the key
 */
void set_environment(s_info *s_i, char *key, char *val)
{
	node *c = get_environment(s_i, key);

	if (c == NULL)
	{
		append_node(s_i->env_keys, key);
		append_node(s_i->env_keys, val);
	}
	else
		amend_node(s_i->env_vals, c - s_i->env_keys->head, val);
}