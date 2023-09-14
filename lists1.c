#include "shell.h"

/**
 * create_list - creates the first node of a new list
 * @type: data type of the data parameter
 *
 * Return: pointer to list header, NULL on failure
 */
list *create_list(char type)
{
	list *newList = NULL;

	newList = malloc(sizeof(list));
	if (!newList)
		return (NULL);
	newList->data_type = type;
	newList->head = NULL;
	return (newList);
}

/**
 * append_node - adds a new node at the end of a list
 * @list: list to be modified
 * @data: data to be stored in the node
 *
 * Return: pointer to list header, NULL on failure
 */
node *append_node(list *list, void *data)
{
	node *new_node;
	node *temp;

	if (!list)
		return (NULL);
	new_node = malloc(sizeof(node));
	if (!new_node)
		return (NULL);
	new_node->d_ptr = data;
	new_node->next = NULL;
	if (list->head == NULL)
	{
		list->head = new_node;
		return (new_node);
	}
	temp = list->head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (new_node);
}

/**
 * insert_node - adds a new node at desired index of a list
 * @list: list to be modified
 * @index: the desired index
 * @data: data to be stored in the node
 *
 * Return: pointer to list header, NULL on failure
 */
node *insert_node(list *list, int index, void *data)
{
	int i;
	node *new_node;
	node *prev = list->head;

	new_node = malloc(sizeof(node));
	if (!new_node)
		return (NULL);

	new_node->d_ptr = data;
	new_node->next = NULL;

	if (index == 0)
	{
		new_node->next = list->head;
		list->head = new_node;
		return (new_node);
	}

	for (i = 0; prev && i < index; i++)
	{
		if (i == index - 1)
		{
			new_node->next = prev->next;
			prev->next = new_node;
			return (new_node);
		}
		prev = prev->next;
	}

	return (NULL);
}

/**
 * free_list - adds a new node at desired index of a list
 * @list: list to be freed
 * @keep_pointers: [boolean] 0 to delete original pointers, 1 to keep
 */
void free_list(list *list, int keep_pointers)
{
	node *temp;

	while (list->head != NULL)
	{
		temp = list->head->next;
		if (!keep_pointers)
			free(list->head->d_ptr);
		free(list->head);
		list->head = temp;
	}
	free(list);
}

/**
 * print_list -Prints elements of the list
 * [WARNING] Currently able to print strings only
 * @list: list to be accessed
 * Return: number of elements in list
 */
size_t print_list(const list *list)
{
	size_t size = 0;
	node *c = list->head;

	while (c != NULL)
	{
		if (c->d_ptr == NULL)
			_puts("(nil)");
		else
			_puts((char *)c->d_ptr);
		_puts("\n");
		c = c->next;
		size++;
	}

	return (size);
}
