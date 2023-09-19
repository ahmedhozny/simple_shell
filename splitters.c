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
				return (bigFree(strArr, j), NULL);
			for (k = 0; k < tmp_size; k++)
				strArr[j][k] = str[(i - tmp_size + 1) + k];

			strArr[j][tmp_size] = '\0';
			tmp_size = 0, j++;
		}
	}
	strArr[j] = NULL;
	return (strArr);
}

/**
 * split - splits a string into 2 strings
 * @str: the whole string
 * @delim: delimiter between strings
 *
 * Return: pointer to the array of strings
 * or NULL if something went wrong
 */
char **split(char *str, char delim)
{
	char **strArr;
	int i, k, size, size1 = 0;

	if (str == NULL || *str == '\0')
		return (NULL);

	size = _strlen(str);
	strArr = malloc(sizeof(*strArr) * 2);
	if (strArr == NULL)
		return (NULL);

	strArr[0] = NULL, strArr[1] = NULL;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == delim)
			break;
		size1++;
	}

	strArr[0] = malloc(sizeof(**strArr) * (size1 + 1));
	strArr[1] = malloc(sizeof(**strArr) * (size - size1));
	if (!strArr[0] || !strArr[1])
		return (bigFree(strArr, 2), NULL);
	for (k = 0; k < size1; k++)
		strArr[0][k] = str[k];
	for (k = 0; k < (size - size1); k++)
		strArr[1][k] = str[k + size1 + 1];

	strArr[0][size1] = '\0', strArr[1][size - size1 - 1] = '\0';
	return (strArr);
}

/**
 * break_chain - parses a command chain, separating commands and operators
 * @s_i: session info
 * @commands: double pointer to store commands
 * @operators: double pointer to store operators
 * Return: 0 on success, -1 on failure
 */
int break_chain(s_info *s_i)
{
	int i, j, stat, k = 0;
	char *c, *s = NULL;
	int curr = 0;

	if (!s_i->cur_line)
		return (-1);
	c = s_i->cur_line;

	for (i = 0; c[i] != '\0'; i++)
	{
		stat = (c[i] == ';') ? CMD_SEP
				: (c[i] == '&' && c[i + 1] == '&') ? CMD_AND
				: (c[i] == '|' && c[i + 1] == '|') ? CMD_OR : 0;
		if (stat == 0)
			continue;
		s = malloc((i - k + 1) * sizeof(char));
		if (!s)
			return (free(s), -1);
		for (j = 0; j < i - k; j++)
			s[j] = s_i->cur_line[k + j];
		s[j] = '\0';
		s_i->cmd_list[curr] = s;
		s_i->ops_list[curr++] = stat;
		k = i + 1 + stat == CMD_AND || stat == CMD_OR ? 1 : 0;
	}
	s = malloc((i - k + 1) * sizeof(char));
	if (!s)
		return (free(s), -1);
	for (j = 0; k + j < i; j++)
		s[j] = s_i->cur_line[k + j];
	s[j] = '\0';
	s_i->cmd_list[curr] = s;
	return (0);
}
