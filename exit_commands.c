#include "shell.h"

/**
 * exit_sh - exits
 * @s_i: session info
 */
void exit_sh(s_info *s_i)
{
	if (s_i->cur_cmd[1] == NULL)
	{
		cleanup(s_i);
		exit((int)s_i->status);
	}
	exit_with_status(s_i);
}

/**
 * exit_with_status - exit program with specified code
 * @s_i: session info
 */
void exit_with_status(s_info *s_i)
{
	int code = _atoi(s_i->cur_cmd[1]);

	if (!exitcode_validity_checker(s_i, s_i->cur_cmd[1], 1))
	{
		cleanup(s_i);
		exit(code);
	}
}

/**
 * _EOF - prepares to close the terminal
 * @s_i: session info
 */
void _EOF(s_info *s_i)
{
	if (isatty(STDIN_FILENO))
		_puts("\n");

	cleanup(s_i);
	exit((int)s_i->status);
}
