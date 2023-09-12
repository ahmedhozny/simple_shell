#include "shell.h"

/**
 * create_list - creates the first node of a new list
 * @data: data to be stored in the node
 * @type: data type of the data parameter
 *
 * Return: pointer to list header, NULL on failure
 */
node *create_list(void *data, char type)
{
	node *head;

	head = malloc(sizeof(node));
	if (head == NULL)
		return (NULL);
	head->d_ptr = data;
	head->data_type = type;
	head->next = NULL;
	return (head);
}

/**
 * append_node - adds a new node at the end of a list
 * @head: A pointer the head of the list.
 * @data: data to be stored in the node
 * @type: data type of the data parameter
 *
 * Return: pointer to list header, NULL on failure
 */
node *append_node(node *head, void *data, char type)
{
	node *new_node;
	node *temp;

	new_node = malloc(sizeof(node));
	if (!new_node)
		return (NULL);
	new_node->d_ptr = data;
	new_node->data_type = type;
	new_node->next = NULL;
	if (head == NULL)
	{
		head = new_node;
		return (head);
	}
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (new_node);
}

/**
 * insert_node - adds a new node at desired index of a list
 * @head: A pointer the head of the list.
 * @index: the desired index
 * @data: data to be stored in the node
 * @type: data type of the data parameter
 *
 * Return: pointer to list header, NULL on failure
 */
node *insert_node(node *head, int index, void *data, char type)
{
	unsigned int i;
	node *new_node;
	node *prev = head;

	new_node = malloc(sizeof(node));
	if (!new_node)
		return (NULL);

	new_node->d_ptr = data;
	new_node->data_type = type;
	new_node->next = NULL;

	if (index == 0)
	{
		new_node->next = head;
		head = new_node;
		return (head);
	}

	for (i = 0; prev && i < index; i++)
	{
		if (i == index - 1)
		{
			new_node->next = prev->next;
			prev->next = new_node;
			return (new_node);
		}
		else
			prev = prev->next;
	}

	return (NULL);
}

/**
 * free_list - adds a new node at desired index of a list
 * @head: A pointer the head of the list.
 * @keep_pointers: [boolean] 0 to delete original pointers, 1 to keep
 */
void free_list(node *head, int keep_pointers)
{
	node *temp;

	while (head != NULL)
	{
		temp = head->next;
		if (!keep_pointers)
			free(head->d_ptr);
		free(head);
		head = temp;
	}
}

/**
 * print_list -Prints elements of the list
 * [WARNING] Currently able to print strings only
 * @h: head of list given
 * Return: number of elements in list
 */
size_t print_list(const node *h)
{
	size_t size = 0;

	while (h != NULL)
	{
		if (h->d_ptr == NULL)
			_puts("(nil)");
		else
			_puts((char *)h->d_ptr);
		h = h->next;
		size++;
	}

	return (size);
}
