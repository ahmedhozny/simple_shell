#include "shell.h"

/**
 * file_permission_error - check if file is actual and executable
 * @s_i: session info
 * @print_error: [boolean] whether error message will be printed
 * Return: 0 if file is okay; -1 otherwise.
 */
int file_permission_error(s_info *s_i, int print_error)
{
	struct stat st;
	char *temp = NULL, *temp2 = NULL;

	if (!s_i->cur_cmd[0])
		return (-1);
	if (stat(s_i->cur_cmd[0], &st) != 0)
		return (command_validity_error(s_i, s_i->cur_cmd[0], 0));
	if (st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
		return (0);

	s_i->status = 126;
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
		_puts(s_i->cur_cmd[0]);
		_puts(": Permission denied\n");
		_putchar(ERROR_FLUSH);
	}
	return (-1);
}

