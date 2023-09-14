#include "shell.h"

/**
 * shell - shell loop function
 * @s_i: session info
 *
 * Return: 1 on Success, 0 on failure
 */
int shell(s_info *s_i)
{
	char **cmd = NULL;
	size_t len = 0;

	while (1)
	{
		free(s_i->cur_line);
		bigFree(cmd, -1);
		cmd = NULL, s_i->cur_line = NULL;
		if (isatty(STDIN_FILENO))
		{
			_puts(PROMPT);
			_putchar(BUF_FLUSH);
		}
		if (getline(&(s_i->cur_line), &len, stdin) < 1)
			_EOF(s_i);

		s_i->cur_line[_strlen(s_i->cur_line) - 1] = '\0';
		cmd = strtow(s_i->cur_line, ' ');
		if (!cmd)
			continue;
		if (exec_builtin(s_i, cmd, cmd[0]))
			continue;
		if (access(cmd[0], X_OK) == -1)
			cmd[0] = search_PATH(s_i, cmd[0]);
		command_validity_checker(s_i, cmd[0], 1);

		if (!s_i->status)
			_execute(s_i, cmd[0], cmd);
	}
	return (0);
}
