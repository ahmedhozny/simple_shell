#include "shell.h"

/**
 * command_validity_error - check if command exists and takes actions
 * @s_i: session info
 * @cmd: command to be checked
 * @print_error: [boolean] whether error message will be printed
 * Return: 0 if command is valid; -1 otherwise.
 */
int command_validity_error(s_info *s_i, char *cmd, int print_error)
{
	char *temp = NULL, *temp2 = NULL;

	s_i->status = 127;
	if (print_error)
	{
		temp = _getenv(s_i, "_")->d_ptr;
		temp2 = convertUnsignedNum(s_i->iter_num);
		if (!temp || !temp2)
		{
			free(temp2);
			return (-1);
		}
		_putchar(BUF_FLUSH);
		_puts(temp);
		_puts(": ");
		_puts(temp2);
		free(temp2);
		_puts(": ");
		_puts(cmd);
		_puts(": not found\n");
		_putchar(ERROR_FLUSH);
	}
	return (0);
}

/**
 * exitcode_validity_checker - checks exit code validity
 * @s_i: session info
 * @exit_code: given exit code
 * @print_error: [boolean] whether error message will be printed
 * Return: 0 if code is valid; -1 otherwise.
 */
int exitcode_validity_checker(s_info *s_i, char *exit_code, int print_error)
{
	char *temp, *temp2;

	if (!_isPositiveNumber(exit_code))
	{
		s_i->status = 2;
		if (print_error)
		{
			temp = _getenv(s_i, "_")->d_ptr;
			temp2 = convertUnsignedNum(s_i->iter_num);
			if (!temp || !temp2)
			{
				free(temp2);
				return (-1);
			}
			_putchar(BUF_FLUSH);
			_puts(temp);
			_puts(": ");
			_puts(temp2);
			free(temp2);
			_puts(": exit: Illegal number: ");
			_puts(exit_code);
			_putchar('\n');
			_putchar(ERROR_FLUSH);
		}
		return (-1);
	}
	return (0);
}

/**
 * cd_validity_checker - checks ability to change directory
 * @s_i: session info
 * @dir: directory
 * @print_error: [boolean] whether error message will be printed
 * Return: 0 if code is valid; -1 otherwise.
 */
int cd_validity_checker(s_info *s_i, char *dir, int print_error)
{
	char *temp, *temp2;

	s_i->status = 2;
	if (print_error)
	{
		temp = _getenv(s_i, "_")->d_ptr;
		temp2 = convertUnsignedNum(s_i->iter_num);
		if (!temp || !temp2)
		{
			free(temp2);
			return (-1);
		}
		_putchar(BUF_FLUSH);
		_puts(temp);
		_puts(": ");
		_puts(temp2);
		free(temp2);
		_puts(": cd: can't cd to ");
		_puts(dir);
		_putchar('\n');
		_putchar(ERROR_FLUSH);
	}
	return (0);
}

/**
 * bad_chain_error - checks syntax errors in the command chain.
 * @s_i: session info
 * @op: operator code that indicates its type
 * @print_error: [boolean] whether error message will be printed
 *
 * Return: 0 if no errors are detected; -1 otherwise.
 */
int bad_chain_error(s_info *s_i, int op, int print_error)
{
	char *temp, *temp2;

	if (op == CMD_SEP || op == CMD_AND || op == CMD_OR)
	{
		s_i->status = 2;
		if (print_error)
		{
			temp = _getenv(s_i, "_")->d_ptr;
			temp2 = convertUnsignedNum(s_i->iter_num);
			if (!temp || !temp2)
			{
				free(temp2);
				return (-1);
			}
			_putchar(BUF_FLUSH);
			_puts(temp);
			_puts(": ");
			_puts(temp2);
			free(temp2);
			temp = op == CMD_SEP ? ";" : op == CMD_AND ? "&&" : "||";
			_puts(": Syntax error: \"");
			_puts(temp);
			_putchar('"');
			_putchar('\n');
			_putchar(ERROR_FLUSH);
		}
		return (-1);
	}
	return (0);
}

/**
 * print_error - print message to stderr
 * @message: message to be printed
 * Return: 1 on Success, 0 otherwise
 */
int print_error(char *message)
{
	return (_putchar(BUF_FLUSH) || _puts(message) || _putchar(ERROR_FLUSH));
}
