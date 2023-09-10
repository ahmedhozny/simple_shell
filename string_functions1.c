#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	size_t i;
	char *new_str;

	if (!str)
		return (NULL);

	new_str = malloc((_strlen(str) + 1) * sizeof(char));
	for (i = 0; str[i] != '\0'; i++)
		new_str[i] = str[i];
	new_str[i] = '\0';
	return (new_str);
}

/**
 * _strlen - finds the length of a string
 * @str: string given
 * Return: size_t of string
 */
size_t _strlen(const char *str)
{
	size_t i;

	if (str == NULL)
		return (0);

	for (i = 0; str[i] != '\0'; i++)
		;

	return (i);
}

/**
 * _strcmp - finds whether two strings are different
 * @s1: 1st string
 * @s2: 2nd string
 * Return: 0 if both are equal, 1 if s1 has a greater character, -1 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0') && (*s2 != '\0'))
	{
		if (*s1 < *s2)
			return (-1);
		else if (*s1 > *s2)
			return (1);
		s1++;
		s2++;
	}

	if (*s1 == '\0' && *s2 == '\0')
		return (0);
	else if (*s1 == '\0')
		return (-1);
	else
		return (1);
}
