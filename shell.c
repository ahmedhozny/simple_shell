#include "shell.h"

/**
 * shell - shell loop function
 * @s_i: session info
 *
 * Return: 1 on Success, 0 on failure
 */
int shell(s_info *s_i)
{
	size_t len = 0;

	while (++s_i->iter_num)
	{
		free(s_i->cur_line);
		s_i->cur_cmd = NULL, s_i->cur_line = NULL;
		s_i->cmd_list = NULL, s_i->ops_list = NULL;
		if (isatty(STDIN_FILENO))
			_puts(PROMPT), _putchar(BUF_FLUSH);
		if (readline(&(s_i->cur_line), &len, s_i->fd) < 1)
			_EOF(s_i);

		handle_input(s_i);
	}
	return (0);
}
