#include "shell.h"

/**
 * command_validity_error - check if command exists and takes actions
 * @s_i: session info
 * @cmd: command to be checked
 * @prints: [boolean] whether error message will be printed
 * Return: 0 if command is valid; -1 otherwise.
 */
int command_validity_error(s_info *s_i, char *cmd, int prints)
{
	struct stat st;

	if (cmd != NULL && stat(cmd, &st) == 0)
		return (0);

	s_i->status = 127;
	if (prints)
		print_error(s_i, s_i->cur_cmd[0], "not found");
	return (-1);
}

/**
 * exitcode_validity_checker - checks exit code validity
 * @s_i: session info
 * @exit_code: given exit code
 * @prints: [boolean] whether error message will be printed
 * Return: 0 if code is valid; -1 otherwise.
 */
int exitcode_validity_checker(s_info *s_i, char *exit_code, int prints)
{
	if (!_isPositiveNumber(exit_code))
	{
		s_i->status = 2;
		if (prints)
			print_error(s_i, "exit: Illegal number", exit_code);
		return (-1);
	}
	return (0);
}

/**
 * cd_validity_checker - checks ability to change directory
 * @s_i: session info
 * @dir: directory
 * @prints: [boolean] whether error message will be printed
 * Return: 0 if code is valid; -1 otherwise.
 */
int cd_validity_checker(s_info *s_i, char *dir, int prints)
{
	char *temp;

	s_i->status = 2;
	if (prints)
	{
		temp = _strcat("can't cd to ", dir, -1);
		print_error(s_i, "cd", temp);
		free(temp);
	}
	return (0);
}

/**
 * bad_chain_error - checks syntax errors in the command chain.
 * @s_i: session info
 * @op: operator code that indicates its type
 * @prints: [boolean] whether error message will be printed
 *
 * Return: 0 if no errors are detected; -1 otherwise.
 */
int bad_chain_error(s_info *s_i, int op, int prints)
{
	char *temp, *temp2;

	if (op == CMD_SEP || op == CMD_AND || op == CMD_OR)
	{
		s_i->status = 2;
		if (prints)
		{
			temp = op == CMD_SEP ? ";" : op == CMD_AND ? "&&" : "||";
			temp = _strcat("\"", temp, -1);
			temp2 = _strcat(temp, "\"", -1);
			print_error(s_i, "Syntax error", temp2);
			free(temp), free(temp2);
		}
		return (-1);
	}
	return (0);
}

/**
 * print_error - prints error messages
 * @s_i: session info
 * @err_1: first part of the message
 * @err_2: second part of the message
 */
void print_error(s_info *s_i, char *err_1, char *err_2)
{
	char *temp;

	temp = convertUnsignedNum(s_i->iter_num);
	if (!temp)
		return;

	_putchar(BUF_FLUSH);
	_puts(s_i->inst_prefix);
	_puts(": ");
	_puts(temp), free(temp);
	_puts(": ");
	_puts(err_1);
	_puts(": ");
	_puts(err_2);
	_putchar('\n');
	_putchar(ERROR_FLUSH);
}
