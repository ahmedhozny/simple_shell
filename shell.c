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
	char *tmp = NULL;

	while (++s_i->iter_num)
	{
		free(s_i->cur_line);
		bigFree(s_i->cur_cmd, -1);
		s_i->cur_cmd = NULL, s_i->cur_line = NULL;
		if (isatty(STDIN_FILENO))
			_puts(PROMPT), _putchar(BUF_FLUSH);
		if (getline(&(s_i->cur_line), &len, stdin) < 1)
			_EOF(s_i);

		s_i->cur_line[_strlen(s_i->cur_line) - 1] = '\0';
		s_i->cur_cmd = strtow(s_i->cur_line, ' ');
		handle_op(s_i);
		if (!s_i->cur_cmd || !s_i->cur_cmd[0])
			continue;
		if (exec_builtin(s_i, s_i->cur_cmd, s_i->cur_cmd[0]))
			continue;
		s_i->status = 0;
		if (s_i->cur_cmd[0][0] != '.' && s_i->cur_cmd[0][0] != '/')
		{
			tmp = search_PATH(s_i, s_i->cur_cmd[0]);
			if (!tmp)
				command_validity_error(s_i, s_i->cur_cmd[0], 1);
			else
			{
				free(s_i->cur_cmd[0]);
				s_i->cur_cmd[0] = tmp;
			}
		}
		else if (access(s_i->cur_cmd[0], X_OK) == -1)
			command_validity_error(s_i, s_i->cur_cmd[0], 1);

		if (!s_i->status)
			_execute(s_i, s_i->cur_cmd[0], s_i->cur_cmd);
	}
	return (0);
}
