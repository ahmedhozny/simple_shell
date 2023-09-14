#include "shell.h"

/**
 * shell - shell loop function
 * @s_i: session info
 *
 * Return: 1 on Success, 0 on failure
 */
int shell(s_info *s_i)
{
	char **cmd = NULL, *line = NULL;
	size_t len = 0;

	while (1)
	{
		bigFree(cmd, -1);
		cmd = NULL;
		if (isatty(STDIN_FILENO))
		{
			_puts(PROMPT);
			_putchar(BUF_FLUSH);
		}
		_EOF(s_i, getline(&line, &len, stdin));
		line[_strlen(line) - 1] = '\0';

		cmd = strtow(line, ' ');
		if (!cmd)
			continue;
		if (exec_builtin(s_i, cmd, cmd[0]))
			continue;
		if (access(cmd[0], X_OK) == -1)
			cmd[0] = search_PATH(s_i, cmd[0]);
		command_validity_checker(s_i, cmd[0], 1);

		if (!s_i->status)
			_execute(s_i, cmd[0], cmd);
		free(line);
	}
	return (0);
}
