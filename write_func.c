#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: 0 on success, -1 on failure
 */
int _putchar(char c)
{
	static char buffer[BUF_SIZE];
	static int cur;

	if (c == BUF_FLUSH || cur >= BUF_SIZE)
	{
		if (write(STDOUT_FILENO, &buffer, cur) == -1)
			return (-1);
		cur = 0;
	}
	if (c != BUF_FLUSH)
	{
		buffer[cur] = c;
		cur++;
	}
	return (0);
}

/**
 * _puts - prints a string
 * @str: The string to be printed
 *
 * Return: 0 on success, -1 on failure
 */
int _puts(char *str)
{
	int i = 0;

	if (str == NULL)
		return (-1);

	while (str[i] != '\0')
		if (_putchar(str[i++]) == -1)
			return (-1);

	return (0);
}
