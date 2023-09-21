#include "shell.h"

/**
 * file_permission_error - check if file is actual and executable
 * @s_i: session info
 * @prints: [boolean] whether error message will be printed
 * Return: 0 if file is okay; -1 otherwise.
 */
int file_permission_error(s_info *s_i, int prints)
{
	struct stat st;

	if (!s_i->cur_cmd[0])
		return (-1);
	if (stat(s_i->cur_cmd[0], &st) != 0)
		return (command_validity_error(s_i, s_i->cur_cmd[0], 0));
	if (st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
		return (0);

	s_i->status = 126;
	if (prints)
		print_error(s_i, s_i->cur_cmd[0], "Permission denied");
	return (-1);
}

/**
 * file_error - give error if a file can't open
 * @s_i: session info
 * @file_name: name of file causing the error
 * @message: message to be printed
 *
 * Return: 0 if file is okay; -1 otherwise.
 */
int file_error(s_info *s_i, char *file_name)
{

	s_i->status = 2;
	_putchar(BUF_FLUSH);
	_puts(s_i->inst_prefix);
	_puts(": 0");
	_puts(": Can't open ");
	_puts(file_name);
	_putchar('\n');
	_putchar(ERROR_FLUSH);
	return (1);
}
