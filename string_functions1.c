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
	if (!new_str)
		return (NULL);

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

/**
 * _strcat - concatenate two strings
 * @s1: 1st string
 * @s2: 2nd string
 * @between: char in the middle
 * Return: new full string
 * On failure NULL
 */
char *_strcat(char *s1, char *s2, char between)
{
	char *newStr;
	size_t i, size1, total_size;

	if (!s1 && !s2)
		return (NULL);

	size1 = _strlen(s1) + ((between != -1) ? 1 : 0);
	total_size = size1 + _strlen(s2);
	newStr = malloc((total_size + 1) * sizeof(*newStr));
	if (newStr == NULL)
		return (NULL);

	for (i = 0; i < total_size; i++)
	{
		if (between != -1 && i == size1 - 1)
			newStr[i] = between;
		else
			newStr[i] = (i < size1) ? s1[i] : s2[i - size1];
	}
	newStr[total_size] = '\0';

	return (newStr);
}

/**
 * *_strchr - searches for the first occurrence of a character in a string
 * @str: string to search into
 * @c: the character to search for
 * Return: pointer to the found character
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
