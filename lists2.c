#include "shell.h"

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
 * Return: 1 on success, 0 otherwise
 */
int delete_node(list *list, unsigned int index)
{
	unsigned int i = 0;
	node *c;
	node *to_delete = NULL;

	if (list->head == NULL)
		return (0);

	c = list->head;
	if (index == 0)
	{
		list->head = list->head->next;
		free(c);
		return (1);
	}

	while (i < index - 1)
	{
		if (!c || !(c->next))
			return (0);
		c = c->next;
		i++;
	}

	to_delete = c->next;
	c->next = to_delete->next;
	free(to_delete);

	return (1);
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
