#include "shell.h"
#include <stdio.h>

/**
 * check_chain - Checks the syntax of a command chain in a string.
 * @str: input string
 *
 * Return: number of chaining elements. or neg number representing chain error
 */
int check_chain(const char *str)
{
	int last_key = -1;
	int i, counter = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ';')
		{
			if (last_key != 0)
				return (CMD_SEP);
			last_key = CMD_SEP, counter++;
		}
		else if (str[i] == '&' && str[i + 1] == '&')
		{
			if (last_key != 0)
				return (CMD_AND);
			last_key = CMD_AND, i++, counter++;
		}
		else if (str[i] == '|' && str[i + 1] == '|')
		{
			if (last_key != 0)
				return (CMD_OR);
			last_key = CMD_OR, i++, counter++;
		}
		else if (str[i] != ' ')
			last_key = 0;
	}

	return (counter);
}

/**
 * handle_input - handles user input and performs operations based on it.
 * @s_i: session info
 */
void handle_input(s_info *s_i)
{
	int op = 0;
	int i, stat;

	s_i->cur_line[_strlen(s_i->cur_line) - 1] = '\0';
	stat = check_chain(s_i->cur_line);
	if (!bad_chain_error(s_i, stat, 1))
	{
		s_i->cmd_list = malloc(sizeof(*s_i->cmd_list) * (stat + 2));
		s_i->ops_list = malloc(sizeof(int) * (stat + 1));
		if (!s_i->cmd_list || !s_i->ops_list)
		{
			free(s_i->cmd_list), free(s_i->ops_list);
			return;
		}
		s_i->cmd_list[stat + 1] = NULL;
		s_i->ops_list[stat] = '\0';
		break_chain(s_i);
		for (i = 0; i < stat + 1; ++i)
		{
			s_i->cur_cmd = strtow(s_i->cmd_list[i], ' ');
			if (!handle_op(s_i, op))
			{
				bigFree(s_i->cmd_list, -1);
				free(s_i->ops_list);
				return;
			}
			op = s_i->ops_list[i];
			bigFree(s_i->cur_cmd, -1);
		}
		bigFree(s_i->cmd_list, -1);
		free(s_i->ops_list);
	}
}

/**
 * handle_op - handle operators in input
 * @s_i: session info
 * @op: operator code that determines execution behavior
 *
 * Return: 1 on Succsess, 0 on Failure
 */
int handle_op(s_info *s_i, int op)
{
	if (!s_i->cur_cmd)
		return (0);
	handle_comments(s_i);
	if (op == 0 || op == CMD_SEP)
		pre_execute(s_i);
	else if (op == CMD_AND && !s_i->status)
		pre_execute(s_i);
	else if (op == CMD_OR && s_i->status)
		pre_execute(s_i);

	return (1);
}

/**
 * handle_comments - handling of comments in input
 * @s_i: seesion info
 */
void handle_comments(s_info *s_i)
{
	static int flag;
	static unsigned long last_iter;
	int i;

	if (last_iter != s_i->iter_num)
		last_iter = s_i->iter_num, flag = 0;
	for (i = 0; s_i->cur_cmd[i]; i++)
	{
		if (s_i->cur_cmd[i][0] == '#')
			flag = 1;
		if (flag)
			free(s_i->cur_cmd[i]), s_i->cur_cmd[i] = NULL;
	}
}

/**
 * search_PATH - searches PATH for needed command
 * @s_i: pointer to current session info
 *
 * Return: full command if exits
 * or NULL if not
 */
char *search_PATH(s_info *s_i)
{
	char **path, *full_cmd;
	node *pathenv = _getenv(s_i, "PATH");
	int i = 0;

	if (!pathenv)
		return (NULL);
	path = strtow(pathenv->d_ptr, ':');
	if (!path)
	{
		s_i->status = 97;
		return (NULL);
	}
	while (path[i])
	{
		full_cmd = _strcat(path[i], s_i->cur_cmd[0], path[i][0]);
		if (!full_cmd)
		{
			bigFree(path, -1);
			s_i->status = 97;
			return (NULL);
		}
		if (!access(full_cmd, X_OK))
			return (bigFree(path, -1), full_cmd);

		free(full_cmd);
		i++;
	}
	bigFree(path, -1);
	return (NULL);
}
