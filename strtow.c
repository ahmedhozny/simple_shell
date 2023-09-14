#include "shell.h"

/**
 * strtow - splits a string into words
 * @str: the whole string
 * @delim: delimiter between strings
 *
 * Return: pointer to the array of strings
 * or NULL if something went wrong
 */
char **strtow(char *str, char delim)
{
	char **strArr;
	int i, k, j = 0, size = 1, tmp_size = 0;

	if (str == NULL || *str == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != delim && (str[i + 1] == delim || str[i + 1] == '\0'))
			size++;

	if (size == 1)
		return (NULL);
	strArr = malloc(sizeof(*strArr) * size);
	if (strArr == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != delim)
			tmp_size++;
		if (str[i] != delim && (str[i + 1] == delim || str[i + 1] == '\0'))
		{
			strArr[j] = malloc(sizeof(**strArr) * (tmp_size + 1));
			if (strArr[j] == NULL)
			{
				bigFree(strArr, j);
				return (NULL);
			}
			for (k = 0; k < tmp_size; k++)
				strArr[j][k] = str[(i - tmp_size + 1) + k];
			tmp_size = 0, j++;
		}
	}
	strArr[j] = NULL;
	return (strArr);
}
