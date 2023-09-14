#include "shell.h"

/**
 * exit_sh - exits
 * @s_i: session info
 * @argv: arguments to be checked
 */
void exit_sh(s_info *s_i, char **argv)
{
	if (argv[1] == NULL)
	{
		cleanup(s_i);
		exit((int)s_i->status);
	}
	exit_with_status(s_i, argv[1]);
}

/**
 * exit_with_status - exit program with specified code
 * @s_i: session info
 * @exit_code: string of the exit status
 */
void exit_with_status(s_info *s_i, char *exit_code)
{
	int code = _atoi(exit_code);

	if (!exitcode_validity_checker(s_i, exit_code, 1))
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
