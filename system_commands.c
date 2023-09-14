#include "shell.h"

/**
 * exit_sh - exits
 * @s_i: session info
 * @argv: arguments to be checked
 */
void exit_sh(s_info *s_i, char **argv)
{
	if (_strcmp(argv[0], "exit"))
		return;
	if (argv[1] == NULL)
		exit((int)s_i->status);

	exit_with_status(s_i, argv[1]);
}

/**
 * exit_with_status - exit program with specified code
 * @s_i: session info
 * @code: string that represents the code
 */
void exit_with_status(s_info *s_i, char *code)
{
	if (!exitcode_validity_checker(s_i, code, 1))
		exit((int)_atoi(code));
}

/**
 * _EOF - prepares to close the terminal
 * @s_i: session info
 * @line_size: line size
 */
void _EOF(s_info *s_i, ssize_t line_size)
{
	if (line_size >= 1)
		return;

	if (isatty(STDIN_FILENO))
		_puts("\n");
	exit((int)s_i->status);
}
