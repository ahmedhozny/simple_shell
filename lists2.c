#include "shell.h"

/**
 * get_index - returns index of specified key
 * @list: list to be accessed
 * @key: key of the node needed
 *
 * Return: pointer to the node found, NULL otherwise
 */
int get_index(list *list, char *key)
{
	node *n = list->head;
	unsigned int index = 0;

	while (n)
	{
		if (!_strcmp(n->d_ptr, key))
			return (index);
		n = n->next;
		index++;
	}
	return (-1);
}

/**
 * get_node - returns the node at specified index
 * @list: list to be accessed
 * @index: index of the node needed
 *
 * Return: pointer to the node found, NULL otherwise
 */
node *get_node(list *list, unsigned int index)
{
	node *c = list->head;

	while (c && index > 0)
	{
		c = c->next;
		index--;
	}

	return (c);
}

/**
 * amend_node - changes data in a node
 * @list: list to be accessed
 * @index: index of the node needed
 * @data: data to be stored in the node
 *
 * Return: pointer to the amended node, NULL otherwise
 */
node *amend_node(list *list, unsigned int index, void *data)
{
	node *c = get_node(list, index);

	if (c == NULL)
		return (NULL);
	c->d_ptr = data;
	return (c);
}

/**
 * delete_node - deletes the node at specified index
 * @list: list to be modified
 * @index: index of the note to be removed
 *
 * Return: 0 on success, 1 otherwise
 */
int delete_node(list *list, unsigned int index)
{
	unsigned int i = 0;
	node *c;
	node *to_delete = NULL;

	if (list->head == NULL)
		return (1);

	c = list->head;
	if (index == 0)
	{
		list->head = list->head->next;
		free(c);
		return (0);
	}

	while (i < index - 1)
	{
		if (!c || !(c->next))
			return (1);
		c = c->next;
		i++;
	}

	to_delete = c->next;
	c->next = to_delete->next;
	free(to_delete);

	return (0);
}

/**
 * list_size - calculates the size of the list
 * @list: list to be accessed
 * Return: size of the given list
 */
int list_size(list *list)
{
	node *c;
	int size = 0;

	if (!list)
		return (0);
	c = list->head;

	while (c != NULL)
	{
		size++;
		c = c->next;
	}

	return (size);
}
