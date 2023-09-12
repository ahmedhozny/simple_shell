#include "shell.h"

/**
 * command_validity_checker - check if command exists and takes actions
 * @s_i: session info
 * @cmd: command to be checked
 * @print_error: [boolean] whether error message will be printed
 * Return: 0 if command is valid; -1 otherwise.
 */
int command_validity_checker(s_info s_i, char *cmd, int print_error)
{
	char *temp;

	if (!cmd)
	{
		s_i.status = 127;
		if (print_error)
		{
			/* pwd needed */
			_puts("[PWD here]");
			_puts(": ");
			temp = convertUnsignedNum(s_i.iter_num);
			_puts(temp);
			free(temp);
			_puts(": ");
			_puts(cmd);
			_puts(": not found");
			_puts("\n");
		}
		return (-1);
	}
	s_i.status = 0;
	return (0);
}

/**
 * exitcode_validity_checker - checks exit code validity
 * @s_i: session info
 * @exit_code: given exit code
 * @print_error: [boolean] whether error message will be printed
 * Return: 0 if code is valid; -1 otherwise.
 */
int exitcode_validity_checker(s_info s_i, char *exit_code, int print_error)
{
	char *temp;

	if (!_isPositiveNumber(exit_code))
	{
		s_i.status = 2;
		if (print_error)
		{
			/* pwd needed */
			_puts("[PWD here]");
			_puts(": ");
			temp = convertUnsignedNum(s_i.iter_num);
			_puts(temp);
			free(temp);
			_puts(": exit: Illegal number: ");
			_puts(exit_code);
			_puts("\n");
		}
		return (-1);
	}
	return (0);
}
