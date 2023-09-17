#include "shell.h"

/**
 * _realloc - reallocate a memory block
 * @ptr: pointer to the memory previously allocated
 * @old_size: size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 *
 * Return: pointer to the new allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newPtr;
	unsigned int min;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	newPtr = malloc(new_size);
	if (newPtr == NULL)
		return (NULL);
	if (ptr == NULL)
		return (newPtr);

	min = (new_size < old_size) ? new_size : old_size;
	while (min--)
		((char *)newPtr)[min] = ((char *)ptr)[min];

	free(ptr);
	return (newPtr);
}

/**
 * bigFree - frees 2d array
 * @ptr: ptr to be free'd
 * @size: size of array
 *
 * Return: pointer to the new allocated memory
 */
void bigFree(char **ptr, int size)
{
	int i;

	if (!ptr)
		return;

	if (size != -1)
		for (i = 0; i < size; i++)
			free(ptr[i]);
	else
		for (i = 0; ptr[i]; i++)
			free(ptr[i]);

	free(ptr);
}

/**
 * cleanup - frees everything at the end
 * @s_i: session info
 *
 * Return: void
 */
void cleanup(s_info *s_i)
{
	_putchar(BUF_FLUSH);
	bigFree(s_i->cur_cmd, -1);
	free_list(s_i->env_keys, 0);
	free_list(s_i->env_vals, 0);
	free(s_i->cur_line);
	free(s_i->prev_dir);
}
