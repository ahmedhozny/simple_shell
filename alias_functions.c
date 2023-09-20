#include "shell.h"

/**
 * init_aliases - initialize alias key-value lists
 * @s_i: session info
 *
 * Return: 1 if initialisation is successful, 0 if not
 */
int init_aliases(s_info *s_i)
{
	list *keys, *values;

	keys = create_list('s'), values = create_list('s');

	if (!keys || !values)
		return (free(keys), free(values), 0);

	s_i->als_keys = keys, s_i->als_vals = values;
	return (1);
}

/**
 * alias_handler - handles command alias operations
 * @s_i: session info
 */
void alias_handler(s_info *s_i)
{
	char **ptr, **split_ptr;

	if (s_i->cur_cmd[1] == NULL)
	{
		print_alias(s_i, NULL);
		return;
	}

	ptr = s_i->cur_cmd + 1;
	while (*ptr)
	{
		split_ptr = split(*ptr, '=');
		if (_strlen(split_ptr[0]) == _strlen(*ptr))
		{
			print_alias(s_i, split_ptr[0]);
			bigFree(split_ptr, 2);
			ptr++;
			continue;
		}

		set_alias(s_i, split_ptr[0], split_ptr[1]);
		free(split_ptr);
		ptr++;
	}
}

/**
 * print_alias - print alias information based on the alias name
 * @s_i: session info
 * @name: name of the alias to print (or NULL to print all aliases)
 */
void print_alias(s_info *s_i, char *name)
{
	node *key = s_i->als_keys->head;
	node *val = s_i->als_vals->head;

	while (key && val)
	{
		if (name == NULL || !_strcmp(key->d_ptr, name))
		{
			_puts(key->d_ptr);
			_puts("='");
			_puts(val->d_ptr);
			_puts("'\n");
			if (name != NULL)
				return;
		}
		key = key->next, val = val->next;
	}

	if (name != NULL)
		_puts("alias: "), _puts(name), _puts(" not found\n"), s_i->status = 1;
}

/**
 * get_alias - retrieve the value of an alias by its name
 * @s_i: session info
 * @name: name of the alias to get
 *
 * Return: pointer to the value found, NULL alias wasn't found
 */
char *get_alias(s_info *s_i, char *name)
{
	node *key = s_i->als_keys->head;
	node *val = s_i->als_vals->head;
	char *tmp;

	while (key && val)
	{
		if (!_strcmp(key->d_ptr, name))
		{
			tmp = get_alias(s_i, val->d_ptr);
			if (tmp != NULL)
				return (tmp);
			else
				return (val->d_ptr);
		}
		key = key->next, val = val->next;
	}

	return (NULL);
}

/**
 * set_alias - Set or update an alias with a given name and value
 * @s_i: session info
 * @name: name of the alias to set or update
 * @value: The value to assign to the alias
 */
void set_alias(s_info *s_i, char *name, char *value)
{
	node *key = s_i->als_keys->head;
	node *val = s_i->als_vals->head;

	while (key && val)
	{
		if (!_strcmp(key->d_ptr, name))
		{
			free(val->d_ptr);
			val->d_ptr = value;
			return;
		}
		key = key->next, val = val->next;
	}
	append_node(s_i->als_keys, name);
	append_node(s_i->als_vals, value);
}
