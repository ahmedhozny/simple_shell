#include "shell.h"

/**
 * handle_op - handle operators in input
 * @s_i: session info
 */
void handle_op(s_info *s_i)
{
	if (!s_i->cur_cmd)
		return;
	handle_comments(s_i);
}

/**
 * handle_comments - handling of comments in input
 * @s_i: seesion info
 */
void handle_comments(s_info *s_i)
{
	int i, flag = 0;

	for (i = 0; s_i->cur_cmd[i]; i++)
	{
		if (s_i->cur_cmd[i][0] == '#')
			flag = 1;
		if (flag)
			free(s_i->cur_cmd[i]), s_i->cur_cmd[i] = NULL;
	}
}
