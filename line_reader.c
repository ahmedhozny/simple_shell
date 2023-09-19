#include "shell.h"

/**
 * readline - reads a line that terminates with EOL
 * @ptr: reference of buffer pointer
 * @n: pointer to allocation memory size
 *
 * Return: Length of the line (EOL included), -1 if error encountered
 */
ssize_t readline(char **ptr, size_t *n)
{
	size_t length = 0, buf_size = 120;
	char *new_ptr;
	char c;
	ssize_t r;

	if (n)
		buf_size = *n < 1 ? 1 : *n;
	*ptr = malloc(buf_size * sizeof(char));
	do {
		r = read_char(&c);
		if (r == -1 || (r < 1 && length == 0))
			return (-1);
		if (length + 1 >= buf_size)
		{
			new_ptr = _realloc(*ptr, buf_size, length + 2);
			if (new_ptr == NULL)
				return (-1);
			buf_size = length + 1;
			*ptr = new_ptr;
		}
		(*ptr)[length++] = c;
	} while (c != '\n');

	(*ptr)[length] = '\0';
	if (n)
		*n = buf_size;
	return ((ssize_t) length);
}

/**
 * read_char - reads a single character from stdin
 * @c: pointer to a character
 *
 * Return: 1 if character is read successfully, -1 otherwise
 */
int read_char(char *c)
{
	int r;

	r = (int) read(STDIN_FILENO, c, 1);
	return (r);
}
