#include "shell.h"

void handle_input(s_info *s_i)
{
	int op = 0;
	int i, stat;

	s_i->cur_line[_strlen(s_i->cur_line) - 1] = '\0';
	stat = check_chain(s_i->cur_line);
	if (!bad_chain_error(s_i, stat, 1))
	{
		s_i->cmd_list = malloc(sizeof(*s_i->cmd_list) * (stat + 1));
		s_i->ops_list = malloc(sizeof(int) * stat);
		if (!s_i->cmd_list || !s_i->ops_list)
		{
			free(s_i->cmd_list), free(s_i->ops_list);
			return;
		}
		break_chain(s_i);
		for (i = 0; i < stat; ++i)
		{
			s_i->cur_cmd = strtow(s_i->cmd_list[i], ' ');
			handle_op(s_i, s_i->cmd_list[i], op);
			op = s_i->ops_list[i];
			bigFree(s_i->cur_cmd, -1);
		}
		s_i->cur_cmd = strtow(s_i->cmd_list[i], ' ');
		handle_op(s_i, s_i->cmd_list[i], op);
		bigFree(s_i->cur_cmd, -1);
		bigFree(s_i->cmd_list, stat + 1);
		free(s_i->ops_list);
	}
}

/**
 * handle_op - handle operators in input
 * @s_i: session info
 */
void handle_op(s_info *s_i, char *cmd, int op)
{
	if (!s_i->cur_cmd)
		return;

	handle_comments(s_i);
	if ((cmd != NULL && op == 0) || op == CMD_SEP)
		pre_execute(s_i);
	else if (op == CMD_AND && !s_i->status)
		pre_execute(s_i);
	else if (op == CMD_OR && s_i->status)
		pre_execute(s_i);
}

/**
 * handle_comments - handling of comments in input
 * @s_i: seesion info
 */
void handle_comments(s_info *s_i)
{
	static int flag;
	static unsigned long last_iter = 0;
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

int check_chain(const char *str)
{
	int last_key = -1;
	int i, counter = 0;

	for (i = 0; str[i] != '\0' && str[i] != '#'; i++)
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
