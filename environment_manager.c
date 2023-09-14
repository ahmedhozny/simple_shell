#include "shell.h"

/**
 * print_env - prints all environment variables
 * @s_i: session info
 *
 * Return: void
 */
void print_env(s_info *s_i)
{
	node *key = s_i->env_keys->head;
	node *val = s_i->env_vals->head;

	while (key && val)
	{
		_puts(key->d_ptr);
		_putchar('=');
		_puts(val->d_ptr);
		_putchar('\n');
		key = key->next;
		val = val->next;
	}
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
	int index = get_index(s_i->env_keys, key);

	if (index == -1)
		return (NULL);

	return (get_node(s_i->env_vals, (unsigned int)index));
}

/**
 * _setenv - sets or updates a key-value pair in the environment
 * @s_i: session info
 * @key: the key for the environment variable
 * @val: the value to associate with the key
 *
 * Return: 1 on Success, 0 on failure
 */
int _setenv(s_info *s_i, char *key, char *val)
{
	node *value = _getenv(s_i, key);

	if (val == NULL)
	{
		if (!append_node(s_i->env_keys, key) || !append_node(s_i->env_vals, val))
			return (0);
	}
	else
		value->d_ptr = val;

	return (1);
}

/**
 * _unsetenv - unsets (deletes) key-value pair in the environment
 * @s_i: session info
 * @key: the key for the environment variable
 *
 * Return: 1 on Success, 0 on failure
 */
int _unsetenv(s_info *s_i, char *key)
{
	int index = get_index(s_i->env_keys, key);

	if (index == -1)
		return (0);

	if (!delete_node(s_i->env_keys, (unsigned int)index) ||
			!delete_node(s_i->env_vals, (unsigned int)index))
		return (0);

	return (1);
}
