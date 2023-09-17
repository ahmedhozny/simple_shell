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
	int index;

	if (!key)
		return (NULL);

	index = get_index(s_i->env_keys, key);
	if (index == -1)
		return (NULL);

	return (get_node(s_i->env_vals, (unsigned int)index));
}

/**
 * _setenv - sets or updates a key-value pair in the environment
 * @s_i: session info
 * @key: key of environment variable
 * @value: value of environment variable
 *
 * Return: 1 on Success, 0 on failure
 */
int _setenv(s_info *s_i, char *key, char *value)
{
	char *newKey = NULL, *newVal = NULL;
	node *value_node;

	newKey = _strdup(key);
	newVal = _strdup(value);
	if (!newKey || !newVal)
	{
		free(newKey);
		free(newVal);
		return (0);
	}
	value_node = _getenv(s_i, newKey);
	if (value_node == NULL)
	{
		if (!append_node(s_i->env_keys, newKey) ||
				!append_node(s_i->env_vals, newVal))
		{
			free(newKey);
			free(newVal);
			return (0);
		}
	}
	else
	{
		free(newKey);
		free(value_node->d_ptr);
		value_node->d_ptr = newVal;
	}

	return (1);
}

/**
 * _unsetenv - unsets (deletes) key-value pair in the environment
 * @s_i: session info
 *
 * Return: 1 on Success, 0 on failure
 */
int _unsetenv(s_info *s_i)
{
	int index;

	if (!s_i->cur_cmd[1])
		return (0);

	index = get_index(s_i->env_keys, s_i->cur_cmd[1]);
	if (index == -1)
		return (0);
	if (delete_node(s_i->env_keys, (unsigned int)index, 0) ||
			delete_node(s_i->env_vals, (unsigned int)index, 0))
		return (0);

	return (1);
}
